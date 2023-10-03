#include <gtk/gtk.h>
#include "lsystem.h"
#include "lsystem_scanner.h"
#include "lsystem_parser.h"
#include "vga_palette.h"

struct Tab {
    char* name;
    GtkWidget* notebook;
    GtkWidget* drawing_area;
    int pageno;
    int n;
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

static void draw_cb(GtkDrawingArea* widget, cairo_t *cr, int w, int h, void* user_data)
{
    struct Tab* t = user_data;
    double x0, y0;

    int pageno = gtk_notebook_get_current_page(GTK_NOTEBOOK(t->notebook));
    if (pageno < 0) {
        return;
    }
    if (pageno != t->pageno) {
        return;
    }

    double min_x = t->min_x, max_x = t->max_x, min_y = t->min_y, max_y = t->max_y;

    double xx = (w - 2) / (max_x - min_x);
    double yy = (h - 2) / (max_y - min_y);
    double kk = xx < yy ? xx : yy;

    int k = 0;
    for (int i = 0; i < t->n; i ++)
    {
        struct Line* it = &t->lines[i];
        int x0 = (int)(1 + (it->x0 - min_x) * kk);
        int y0 = (int)(1 + (it->y0 - min_y) * kk); y0 = h - y0 - 1;
        int x1 = (int)(1 + (it->x1 - min_x) * kk);
        int y1 = (int)(1 + (it->y1 - min_y) * kk); y1 = h - y1 - 1;
        double r = (vga_palette[it->c] >> 16) & 0xff;
        double g = (vga_palette[it->c] >> 8) & 0xff;
        double b = (vga_palette[it->c] >> 0) & 0xff;
        cairo_set_source_rgb(cr, r/256., g/256., b/256.);
        cairo_move_to(cr, x0, y0);
        cairo_line_to(cr, x1, y1);
        cairo_stroke(cr);
    }
}

static void destroy_tabs(struct App* app) {
    int i;
    for (i = 0; i < app->ntabs; i=i+1) {
        free(app->tabs[i]->lines);
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

        int i;
        for (i = 0; i < app->ntabs; i=i+1) {
            gtk_notebook_remove_page(GTK_NOTEBOOK(app->notebook), 0);
        }

        destroy_tabs(app);

        int l;
        char *W;
        int pageno = 0;
        parser_print(p);

        for (g = parser_group_start(p); g; g = group_next(g), pageno = pageno+1) {
            struct Lines lines; memset(&lines, 0, sizeof(lines));
            l = group_get_order(g);
            if (l == 0) {
                l = 2;
            }
            name = group_get_name(g);
            W = lsystem(g, l);
            turtle(&lines, g, W);
            free(W);

            t = calloc(1, sizeof(struct Tab));
            t->n = lines.n;
            t->lines = lines.lines;
            t->name = strdup(name);
            lines_normilize(lines.lines, lines.n, &t->min_x, &t->max_x, &t->min_y, &t->max_y);
            t->drawing_area = gtk_drawing_area_new();
            t->notebook = app->notebook;
            t->pageno = pageno;
            gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(t->drawing_area), draw_cb, t, NULL);
            gtk_widget_set_vexpand(t->drawing_area, TRUE);
            gtk_widget_set_hexpand(t->drawing_area, TRUE);

            label = gtk_label_new(name);
            gtk_notebook_append_page(GTK_NOTEBOOK(app->notebook), t->drawing_area, label);

            if (app->ntabs >= app->capacity) {
                app->capacity = (app->capacity+1)*2;
                app->tabs = realloc(app->tabs, app->capacity*sizeof(struct Tab*));
            }
            app->tabs[app->ntabs++] = t;
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
on_file_open(GObject* source, GAsyncResult* res, gpointer user_data)
{
    struct App* app = (struct App*)user_data;
    GFile* file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), res, NULL);
    if (file) {
        char* path = g_file_get_path(file);
        open_file(path, app);
        g_free(path);
        g_object_unref(file);
    }
}

static void
open_cb (GSimpleAction *simple, GVariant      *parameter, gpointer user_data)
{
    GtkFileDialog* dialog = gtk_file_dialog_new();
    gtk_file_dialog_open(dialog, NULL, NULL, on_file_open, user_data);
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
    GtkWidget* toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* item;

    item = gtk_button_new_from_icon_name("document-open");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(item), "lsystem.open");
    gtk_widget_set_tooltip_text(item, "open");
    gtk_button_set_has_frame(GTK_BUTTON(item), false);
    gtk_box_append(GTK_BOX(toolbar), item);

    item = gtk_button_new_from_icon_name("document-save");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(item), "lsystem.save");
    gtk_widget_set_tooltip_text(item, "save");
    gtk_button_set_has_frame(GTK_BUTTON(item), false);
    gtk_box_append(GTK_BOX(toolbar), item);

    gtk_box_append(GTK_BOX(toolbar), gtk_separator_new(GTK_ORIENTATION_VERTICAL));

    item = gtk_button_new_from_icon_name("media-playback-start");
    gtk_actionable_set_action_name(GTK_ACTIONABLE(item), "lsystem.run");
    gtk_widget_set_tooltip_text(item, "run");
    gtk_button_set_has_frame(GTK_BUTTON(item), false);
    gtk_box_append(GTK_BOX(toolbar), item);
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

    scrolled = gtk_scrolled_window_new();
    scrolled_log = gtk_scrolled_window_new();
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

    gtk_window_set_child(GTK_WINDOW(window), main_box);
    gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW(scrolled), text_view);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_log), log_view);

    gtk_box_append(GTK_BOX(main_box), create_toolbar(app));
    gtk_box_append(GTK_BOX(main_box), box);

    gtk_box_append(GTK_BOX(box), notebook);
    gtk_box_append(GTK_BOX(box), right_box);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    gtk_paned_set_start_child(GTK_PANED(right_box), scrolled);
    gtk_paned_set_resize_start_child(GTK_PANED(right_box), TRUE);
    gtk_paned_set_shrink_start_child(GTK_PANED(right_box), TRUE);
    gtk_paned_set_end_child(GTK_PANED(right_box), scrolled_log);
    gtk_paned_set_resize_end_child(GTK_PANED(right_box), TRUE);
    gtk_paned_set_shrink_end_child(GTK_PANED(right_box), FALSE);

    app->notebook = notebook;
    app->text_view = text_view;
    app->log_view = log_view;
    app->window = window;

    compile(app);

    gtk_window_present(GTK_WINDOW(window));

    const char *accels[] = {"F5", NULL};
    gtk_application_set_accels_for_action(GTK_APPLICATION(a), "lsystem.run", accels);
};

int main(int argc, char** argv) {
    struct App app;
    memset(&app, 0, sizeof(struct App));

    GtkApplication *a = gtk_application_new(
        "org.lsystem",
        G_APPLICATION_DEFAULT_FLAGS
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
