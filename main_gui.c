#include <gtk/gtk.h>
#include "lsystem.h"
#include "lsystem_scanner.h"
#include "lsystem_parser.h"
#include "colormap_vga1.h"

struct App {
    cairo_surface_t *surface;
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

    YY_BUFFER_STATE state = yy_scan_string(text);
    while (yyparse(p) && !parser_has_error(p));
    yy_delete_buffer(state);

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
        lines_normilize(lines, &app->min_x, &app->max_x, &app->min_y, &app->max_y);
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

static void close_window(GtkWidget* widget, struct App* app)
{   
    if (app->surface)
    {
        cairo_surface_destroy(app->surface);
    }

    gtk_main_quit();
}

int main(int argc, char** argv) {
    struct App app;
    GtkWidget* window;
    GtkWidget* box;
    GtkWidget* drawing_area;
    GtkWidget* text_view;
    GtkTextBuffer *buffer;
    const char * text = 
"flower { \n \
    axiom F[+F+F][-F-F][++F][--F]F \n \
    F=FF[++F][+F][F][-F][--F] \n \
    alpha 1.5707963267948966192313216916398 \n \
    theta 0.19634954084936207740391521145497 \n \
} \n \
";

    memset(&app, 0, sizeof(struct App));

    gtk_disable_setlocale(); // parser works incorrect with locale set

    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW (window), 1024, 768);
  
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    drawing_area = gtk_drawing_area_new();
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    gtk_text_buffer_set_text (buffer, text, -1);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_box_pack_start(GTK_BOX(box), drawing_area, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(box), text_view, TRUE, TRUE, 0);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    app.drawing_area = drawing_area;
    app.text_view = text_view;
    compile(&app);

    gtk_widget_show_all (window);

    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event_cb), &app);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), &app);
    g_signal_connect(window, "key-press-event", G_CALLBACK(key_press_event), &app);
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), &app);

    gtk_main();    
    return 0;
}
