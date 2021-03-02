#include <gtk/gtk.h>
#include "lsystem.h"
#include "lsystem_scanner.h"
#include "lsystem_parser.h"
#include "colormap_vga1.h"

struct Tab {
    char* name;
    cairo_surface_t *surface;
    GtkWidget* notebook;
    GtkWidget* drawing_area;
    int pageno;
    struct Line* lines;
    double min_x;
    double max_x;
    double min_y;
    double max_y;
};

struct App {
    GtkWidget* window;
    GtkWidget* notebook;
    GtkWidget* text_view;
    GtkWidget* log_view;
    struct Tab** tabs;
    int ntabs;
    int capacity;
};

static void clear_surface(cairo_surface_t *surface)
{
    cairo_t *cr;
    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

static gboolean draw_cb(GtkWidget* widget, cairo_t* cr, struct Tab* t)
{
    double x0, y0;

    if (t->surface == NULL) {
        return TRUE;
    }

    int pageno = gtk_notebook_get_current_page(GTK_NOTEBOOK(t->notebook));
    if (pageno < 0) {
        return TRUE;
    }
    if (pageno != t->pageno) {
        return TRUE;
    }

    cairo_set_source_surface(cr, t->surface, 0, 0);
    cairo_paint(cr);

    return TRUE;
}

static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, struct Tab* t)
{
    if (t->surface) {
        cairo_surface_destroy(t->surface);
    }
    int w = gtk_widget_get_allocated_width(widget);
    int h = gtk_widget_get_allocated_height(widget);

    t->surface = gdk_window_create_similar_surface(
        gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
        w, h);

    clear_surface(t->surface);

    double min_x = t->min_x, max_x = t->max_x, min_y = t->min_y, max_y = t->max_y;

    double xx = (w - 2) / (max_x - min_x);
    double yy = (h - 2) / (max_y - min_y);
    double kk = xx < yy ? xx : yy;

    cairo_t* cr = cairo_create (t->surface);

    int k = 0;
    for (struct Line* it = t->lines; it != NULL; it=it->next, k++)
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

    cairo_destroy (cr);

    return TRUE;
}

static void destroy_tabs(struct App* app) {
    struct Line* cur = NULL;
    struct Line* next = NULL;
    int i;
    for (i = 0; i < app->ntabs; i=i+1) {
        if (app->tabs[i]->surface)
        {
            cairo_surface_destroy(app->tabs[i]->surface);
            app->tabs[i]->surface = NULL;
        }
        if (app->notebook) {
            gtk_widget_destroy(app->tabs[i]->drawing_area);
        }
        cur = app->tabs[i]->lines;
        while (cur) {
            next = cur->next;
            free(cur);
            cur = next;
        }
        free(app->tabs[i]->name);
        free(app->tabs[i]);
    }
    app->ntabs = 0;
}

static void
log_function(struct App* app, const char* text) { 
    GtkTextIter start, end;
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->log_view));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    //gtk_text_buffer_delete(buffer, &start, &end);
    //gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_insert(buffer, &end, text, -1);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(app->log_view), &end, FALSE, FALSE, 0, 0);

    fprintf(stderr, "%s", text);
}

static void compile(struct App* app) {
    struct Parser* p = parser_new((log_function_t)log_function, app);
    struct Group* g = NULL;
    struct Tab* t;
    
    GtkTextIter start, end;
    GtkWidget* label;
    gchar* text;

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->log_view));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_delete(buffer, &start, &end);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->text_view));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);

    yyset_lineno(1);
    YY_BUFFER_STATE state = yy_scan_string(text);
    while (yyparse(p) && !parser_has_error(p));
    yy_delete_buffer(state);
    yylex_destroy();

    if (!parser_has_error(p)) {
        struct Line* lines = NULL;
        const char* name;

        destroy_tabs(app);

        int l;
        char *W;
        int pageno = 0;
        parser_print(p);

        for (g = parser_group_start(p); g; g = group_next(g), pageno = pageno+1) {
            l = group_get_order(g);
            if (l == 0) {
                l = 2;
            }
            name = group_get_name(g);
            W = lsystem(g, l);
            lines = turtle(g, W); 
            free(W);

            t = calloc(1, sizeof(struct Tab));
            t->lines = lines;
            t->name = strdup(name);

            if (lines != NULL) {
                lines_normilize(lines, &t->min_x, &t->max_x, &t->min_y, &t->max_y);
            }
            t->drawing_area = gtk_drawing_area_new();
            t->notebook = app->notebook;
            t->pageno = pageno;
            g_signal_connect(t->drawing_area, "configure-event", G_CALLBACK(configure_event_cb), t);
            g_signal_connect(t->drawing_area, "draw", G_CALLBACK(draw_cb), t);

            label = gtk_label_new(name);
            gtk_notebook_append_page(GTK_NOTEBOOK(app->notebook), t->drawing_area, label);

            if (app->ntabs >= app->capacity) {
                app->capacity = (app->capacity+1)*2;
                app->tabs = realloc(app->tabs, app->capacity*sizeof(struct Tab*));
            }
            app->tabs[app->ntabs++] = t;

            gtk_widget_show(t->drawing_area);
            gtk_widget_show(label);
        }

        gtk_text_buffer_delete(buffer, &start, &end);
        gtk_text_buffer_get_start_iter(buffer, &start);
        gtk_text_buffer_insert(buffer, &start, text, -1);
    } else {
        int lineno = 0;

        lineno = parser_get_error_line(p);
        GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app->text_view));
        GtkTextIter start, end;
        gtk_text_buffer_get_iter_at_line_offset(buffer, &start, lineno-1, 0);
        gtk_text_buffer_get_iter_at_line_offset(buffer, &end, lineno, 0);

        char* new_text = NULL;
        gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        if (strlen(text) > 0) {
            gtk_text_buffer_delete(buffer, &start, &end);
            new_text = malloc(strlen(text)+1024); new_text[0] = 0;
            strcat(new_text, "<span background=\"red\">");
            strcat(new_text, text);
            strcat(new_text, "</span>");
            gtk_text_buffer_get_iter_at_line_offset(buffer, &start, lineno-1, 0);
            gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(app->text_view), &end, FALSE, FALSE, 0, 0);
            gtk_text_buffer_place_cursor(buffer, &end);
            gtk_text_buffer_insert_markup(buffer, &start, new_text, -1);
        }
        g_free(text);
        free(new_text);
    }

    g_free(text);
    parser_free(p);
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
        gchar* utf8 = g_utf8_make_valid(buf, size);
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(buffer, &end, utf8, strlen(utf8));
        g_free(utf8);
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
    GtkWidget* right_box; // text and log
    GtkWidget* text_view;
    GtkWidget* log_view;
    GtkWidget* notebook;
    GtkWidget* scrolled;
    GtkWidget* scrolled_log;
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
    right_box = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    scrolled_log = gtk_scrolled_window_new(NULL, NULL);
    text_view = gtk_text_view_new();
    log_view = gtk_text_view_new();
    notebook = gtk_notebook_new();
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    gtk_text_buffer_set_text (buffer, text, -1);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);

    gtk_text_view_set_editable(GTK_TEXT_VIEW(log_view), FALSE);
    gtk_widget_set_can_focus(log_view, FALSE);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(log_view), TRUE);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_container_add(GTK_CONTAINER(scrolled), text_view);
    gtk_container_add(GTK_CONTAINER(scrolled_log), log_view);

    gtk_box_pack_start(GTK_BOX(main_box), create_toolbar(app), FALSE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(main_box), box, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(box), notebook, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(box), right_box, TRUE, TRUE, 0);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    gtk_paned_pack1(GTK_PANED(right_box), scrolled, TRUE, FALSE);
    gtk_paned_pack2(GTK_PANED(right_box), scrolled_log, TRUE, FALSE);

    app->notebook = notebook;
    app->text_view = text_view;
    app->log_view = log_view;
    app->window = window;

    compile(app);

    gtk_widget_show_all (window);

    const char *accels[] = {"F5", NULL};
    gtk_application_set_accels_for_action(GTK_APPLICATION(a), "lsystem.run", accels);
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

    fprintf(stderr, "done\n");
    app.notebook = NULL;
    destroy_tabs(&app);
    free(app.tabs);

    return status;
}
