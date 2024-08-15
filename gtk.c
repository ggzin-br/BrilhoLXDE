#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>

// Um programa de automação do Pedro - Livre para modificação e distribuição
/*
Descrição:
É usado o GTK2 para abrir uma janela simples que tem somente um slide (scale)
*/

/* Função que será chamada no G_CALLBACK */
void call_change(GtkRange *range, gpointer user_data) {
    gdouble valor = gtk_range_get_value(range);
    troca_valor(valor);
}

int main(int argc, char *argv[], char *envp[]) {

    /* Declaração de variáveis */
    GtkWidget *win = NULL;
    GtkWidget *scale = NULL;
    GtkObject *step = gtk_adjustment_new(50, 0, 101, 1, 1, 1);

    /* Obtenção do usuário root */
    geteuid() != 0 ? admin(envp, argv[0]) : NULL;

    /* GTK+ */
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init(&argc, &argv);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    /* Janela inicial */
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER (win), 8);

    gtk_window_set_title(GTK_WINDOW (win), "Brilho LXDE");
    gtk_window_set_position(GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(win, 400, 100);

    gtk_widget_realize(win);

    /* Construção do slide do brilho */
    scale = gtk_hscale_new(step);
    g_signal_connect(scale, "value_changed", G_CALLBACK(call_change), NULL);
    gtk_container_add(GTK_CONTAINER(win), scale);


    /* Loop para manter a janela aberta */
    gtk_widget_show_all(win);
    g_signal_connect(win, "destroy", gtk_main_quit, NULL);
    gtk_main();

    return 0;
}

// Por algum motivo ainda o vazamento de memória deste programa é altíssimo, não sei resolver...
