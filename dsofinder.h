#ifndef DSOFINDER_H
#define DSOFINDER_H

#include <QMainWindow>
#include "QMessageBox"
#include "QColor"
#include "QPainter"
#include <QColormap>
#include <QPoint>
#include <QSettings>
#include <QElapsedTimer>
#include <stdlib.h>
#include <stdio.h>
#include <QColorDialog>
#include <QFile>
#include <QInputDialog>
#include <QTranslator>

namespace Ui {
    class DsoFinder;
}

class DsoFinder : public QMainWindow
{
    Q_OBJECT

public:
    // DEFINDE STRUCTURES FOR OFTEN USED DATA_STORAGE_OBJECTS
    struct rgb_value {
        int min;
        int max;
    };

    struct pixel_pos {
        int x_pos;
        int y_pos;
    };

    struct pixel_data {
        rgb_value r;
        rgb_value g;
        rgb_value b;
        pixel_pos pos;
        bool negating;

        pixel_data():negating(false){}
    };

    struct item_shape {
        int pixelcount;
        pixel_data* pixel;
        int needed; //NEEDED DISCOVERYS FOR SUCCESS
    };

    struct item {
        const char* caption;
        int shapecount;
        item_shape* shape;
        QString item_type;
        QColor color;
        QColor alt_color;
        Qt::PenStyle penstyle;

        item():item_type("standard"){}
    };

    struct event {
        QString caption;
        int id;
        int itemcount;
    };

    struct event_data {
        event* events;
        int eventcount;
    };

    struct configuration {
        int vid;

        QPoint position_small;
        QSize size;
        bool ontop;

        QColor items_standard_color;
        QColor items_event_color;
        int waittime;
        bool show_searchtimer;
        bool useitems_basic;
        bool useitems_adventure;
        bool usehalfsize;
        int use_event;
        QVector<QString> bg_caption;
        int use_bg;

        bool jump_position;
        bool stay_big;
        QString language;
    };

    //PIXELFINDER_RELATED OBJECTS/VARIABLES
    item* items;
    int itemcount;
    int*** pixels;
    int shape_disc,shape_negating;
    int avatar_width, avatar_heigth;
    bool item_found;
    QVector<QVector<int> > discovery;

    //BUILDING_SITE_RELATED OBJECTS/VARIABLES
    bool bg_exist;
    int bg_count;
    QImage BGImage,divImage;
    QPainter paint_dev2;
    QRgb bg_imgrgb,divrgb;
    int count_ok,count_ok_min,count_brigth,count_brigth_min,count_double;

    //COMMON USED OBJECTS/VARIABLES
    QString currentversion;
    int cvid;

    QMessageBox msgbox;
    QElapsedTimer timer;
    QSettings* configfile;
    configuration config;
    FILE* results;

    QPixmap originalPixmap;
    QImage originalImage;
    QPainter paint_dev;
    QPen pen_dev;
    QRgb imgrgb;

    int x,y;
    int i,k,j,r,g,b;

    int totaldiscoverys;
    int d_width,d_heigth,borderbox;

    bool debug;
    bool current_ontop_windowsetting;
    bool current_small_window;
    bool options_visible;

    explicit DsoFinder(int argc,char* argv[],QWidget *parent = 0);
    ~DsoFinder();

    //DECLARATION OF IMPLEMENTED FUNCTIONS
    int get_method();
    int get_bgcount();
    void set_gui(bool small, bool is_debug);
    void setactive(bool active);
    void activate_buttons(bool activate);
    void log_discoverys();
    void validate_discoverys();
    void draw_valids();
    void draw_discovery(QPoint coords, QColor color, Qt::PenStyle style);
    void init_items();
    event_data get_events();
    void load_settings();
    void load_background();
    void check_version();
    void init_ui_options();
    void save_settings();
    void set_windowparameters(int value);
    void set_optionwindow(bool visible);
    bool is_green(int r, int g, int b);
    bool is_brigth(int g);

    void populate_event_combo();
protected:
    void resizeEvent(QResizeEvent* event);
    void changeEvent(QEvent *e);


private slots:
    void on_takeButton_clicked();

    void on_resizeButton_clicked();

    void on_debugloadButton_clicked();

    void on_findButton_clicked();

    void on_debugsaveButton_clicked();

    void on_methodtab_currentChanged(int index);

    void on_savebgButton_clicked();

    void on_showbgButton_clicked();

    void on_ontopcheckbox_stateChanged(int is_checked);

    void on_optionButton_clicked();

    void on_waittime_slider_sliderMoved(int position);

    void on_waittime_lineEdit_textEdited(const QString &arg1);

    void on_searchtimercheckBox_stateChanged(int arg1);

    void on_itembasiccheckBox_stateChanged(int arg1);

    void on_itemadventurecheckBox_stateChanged(int arg1);

//    void on_itemhalloween13checkBox_stateChanged(int arg1);

//    void on_itemchristmas13checkBox_stateChanged(int arg1);

    void on_jumpcheckBox_stateChanged(int arg1);

    void on_staybigcheckBox_stateChanged(int arg1);

//    void on_itemeastern14checkBox_stateChanged(int arg1);

    void on_colorstandardpushButton_clicked();

    void on_coloreventpushButton_clicked();

    void on_itemeventcomboBox_activated(int index);

    void on_bgcomboBox_activated(int index);

    void on_bg_editpushButton_clicked();

    void on_bgdeletepushButton_clicked();

    void select_language(QString language);

    void on_halfsizecheckbox_stateChanged(int arg1);

private:
    Ui::DsoFinder *ui;
    QTranslator lang;
};

#endif // DSOFINDER_H
