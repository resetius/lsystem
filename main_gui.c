#include <gtk/gtk.h>
#include "lsystem.h"
#include "lsystem_scanner.h"
#include "lsystem_parser.h"
#include "colormap_vga1.h"

struct App {
    cairo_surface_t *surface;
    GtkWidget* window;
    GtkWidget* drawing_area;
    GtkWidget* text_view;
    struct Line* lines;
    double min_x;
    double max_x;
    double min_y;
    double max_y;
};

static void clear_surface(cairo_surface_t *surface)
{
    cairo_t *cr;
    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, struct App* app)
{
    if (app->surface)
        cairo_surface_destroy(app->surface);

    app->surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width(widget),
                                                gtk_widget_get_allocated_height(widget));

    clear_surface(app->surface);

    return TRUE;
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, struct App*  app)
{
    double x0, y0;

    int w = gtk_widget_get_allocated_width (widget);
    int h = gtk_widget_get_allocated_height (widget);

    if (app->lines == NULL) {
        return TRUE;
    }

    double min_x = app->min_x, max_x = app->max_x, min_y = app->min_y, max_y = app->max_y;

    double xx = (w - 2) / (max_x - min_x);
    double yy = (h - 2) / (max_y - min_y);
    double kk = xx < yy ? xx : yy;

    int k = 0;
    for (struct Line* it = app->lines; it != NULL; it=it->next, k++)
    {
        int x0 = (int)(1 + (it->x0 - min_x) * kk); 
        int y0 = (int)(1 + (it->y0 - min_y) * kk); y0 = h - y0 - 1;
        int x1 = (int)(1 + (it->x1 - min_x) * kk);
        int y1 = (int)(1 + (it->y1 - min_y) * kk); y1 = h - y1 - 1;
        cairo_set_source_rgb(cr, colormap_vga1[it->c][0]/256., colormap_vga1[it->c][1]/256., colormap_vga1[it->c][2]/256.);
        cairo_move_to(cr, x0, y0);
        cairo_line_to(cr, x1, y1);
        cairo_stroke(cr);
    }

    return TRUE;
}

static void compile(struct App* app) {
    struct Parser* p = parser_new();
    struct Group* g = NULL;
    
    GtkTextIter start, end;
    gchar* text;
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->text_view));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);

    yyset_lineno(1);
    YY_BUFFER_STATE state = yy_scan_string(text);
    while (yyparse(p) && !parser_has_error(p));
    yy_delete_buffer(state);
    yylex_destroy();

    if (!parser_has_error(p)) {
        struct Line* cur = NULL;
        struct Line* next = NULL;
        struct Line* lines = NULL;
        int l;
        char *W;
        parser_print(p);
        g = parser_group_start(p);
        l = group_get_order(g);
        if (l == 0) {
            l = 2;
        }
        W = lsystem(g, l);
        lines = turtle(g, W); 
        free(W);
        cur = app->lines;
        while (cur) {
            next = cur->next;
            free(cur);
            cur = next;
        }
        app->lines = lines;
        if (lines != NULL) {
            lines_normilize(lines, &app->min_x, &app->max_x, &app->min_y, &app->max_y);
        }
    } else {
        parser_print_error(p);
    }

    free(text);
    parser_free(p);
}

static gboolean key_press_event(GtkWidget* widget, GdkEventKey* event, struct App* app) 
{
    if (event->type == GDK_KEY_PRESS) {
        if (event->keyval == GDK_KEY_F5) {
            fprintf(stderr, "compile\n");
            compile(app);
            gtk_widget_queue_draw(app->drawing_area);
        }
    }
    return FALSE;
}

static void open_file(char* filename, struct App* app) {
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        return;
    }
    char buf[1024];
    GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->text_view));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_delete(buffer, &start, &end);

    int size;
    while ((size = fread(buf, 1, sizeof(buf), f)) > 0) {
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(buffer, &end, buf, size);
    }

    fclose(f);

    snprintf(buf, sizeof(buf), "lsystem (%s)", filename);
    gtk_window_set_title(GTK_WINDOW(app->window), buf);
}

static void
open_cb (GSimpleAction *simple, GVariant      *parameter, gpointer user_data)
{
    struct App* app = (struct App*)user_data;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new (
        "Open File",
        GTK_WINDOW(app->window),
        action,
        "_Cancel",
        GTK_RESPONSE_CANCEL,
        "_Open",
        GTK_RESPONSE_ACCEPT,
        NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        open_file (filename, app);
        g_free (filename);
    }

    gtk_widget_destroy (dialog);

    fprintf(stderr, "open\n");
}

static void
save_cb (GSimpleAction *simple, GVariant      *parameter, gpointer user_data)
{
    fprintf(stderr, "save\n");
}

static void
run_cb (GSimpleAction *simple, GVariant      *parameter, gpointer user_data)
{
    struct App* app = (struct App*)user_data;
    compile(app);
    gtk_widget_queue_draw(app->drawing_area);
}

static GtkWidget* create_toolbar(struct App* app) {
    GtkWidget* toolbar;
    GtkToolItem* item;

    toolbar = gtk_toolbar_new ();

    item = gtk_tool_button_new(gtk_image_new_from_icon_name("document-open", GTK_ICON_SIZE_SMALL_TOOLBAR), "open");
    gtk_tool_item_set_tooltip_text(item, "open");
    gtk_actionable_set_action_name(GTK_ACTIONABLE (item), "lsystem.open");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1); 

    item = gtk_tool_button_new(gtk_image_new_from_icon_name("document-save", GTK_ICON_SIZE_SMALL_TOOLBAR), "save");
    gtk_tool_item_set_tooltip_text(item, "save");
    gtk_actionable_set_action_name(GTK_ACTIONABLE (item), "lsystem.save");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1); 

    item = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item = gtk_tool_button_new(gtk_image_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR), "run");
    gtk_tool_item_set_tooltip_text(item, "run");
    gtk_actionable_set_action_name(GTK_ACTIONABLE (item), "lsystem.run");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1); 

    return toolbar;
}

static void on_app_activate(GApplication *a, struct App* app) {
    GtkWidget* window;
    GtkWidget* box; // drawing_area and text
    GtkWidget* main_box; // toolbar and other
    GtkWidget* drawing_area;
    GtkWidget* text_view;
    GtkTextBuffer *buffer;
    GActionEntry action_entries[] =
    {
        {"open", open_cb, NULL, NULL, NULL},
        {"save", save_cb, NULL, NULL, NULL},
        {"run", run_cb, NULL, NULL, NULL}
    };
    GSimpleActionGroup* group;
    const char * text = 
"flower { \n \
    axiom F[+F+F][-F-F][++F][--F]F \n \
    F=FF[++F][+F][F][-F][--F] \n \
    alpha 1.5707963267948966192313216916398 \n \
    theta 0.19634954084936207740391521145497 \n \
} \n \
";

    window = gtk_application_window_new(GTK_APPLICATION(a));
    gtk_window_set_default_size (GTK_WINDOW (window), 1024, 768);
    group = g_simple_action_group_new ();
    g_action_map_add_action_entries (G_ACTION_MAP(group), action_entries, G_N_ELEMENTS (action_entries), app);
    gtk_widget_insert_action_group (window, "lsystem", G_ACTION_GROUP (group));

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    drawing_area = gtk_drawing_area_new();
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    gtk_text_buffer_set_text (buffer, text, -1);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);

    gtk_container_add(GTK_CONTAINER(window), main_box);

    gtk_box_pack_start(GTK_BOX(main_box), create_toolbar(app), FALSE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(main_box), box, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box), drawing_area, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(box), text_view, TRUE, TRUE, 0);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    app->drawing_area = drawing_area;
    app->text_view = text_view;
    app->window = window;

    compile(app);

    gtk_widget_show_all (window);

    const char *accels[] = {"F5", NULL};
    gtk_application_set_accels_for_action(GTK_APPLICATION(a), "lsystem.run", accels);

    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event_cb), app);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), app);
    g_signal_connect(window, "key-press-event", G_CALLBACK(key_press_event), app);
};

int main(int argc, char** argv) {
    struct App app;
    memset(&app, 0, sizeof(struct App));

    GtkApplication *a = gtk_application_new(
        "org.lsystem", 
        G_APPLICATION_FLAGS_NONE
    );

    gtk_disable_setlocale(); // parser works incorrect with locale set

    g_signal_connect(a, "activate", G_CALLBACK(on_app_activate), &app);
    
    int status = g_application_run(G_APPLICATION(a), argc, argv);
    g_object_unref(a);

    if (app.surface)
    {
        cairo_surface_destroy(app.surface);
    }

    return status;
}
