#include "dsofinder.h"
#include "ui_dsofinder.h"

void DsoFinder::set_gui(bool small, bool is_debug)
{
    if(small){
        set_windowparameters(0);
        current_small_window = true;
        ui->findButton->hide();
        ui->resizeButton->hide();
        ui->notelabel->hide();
        ui->debugloadButton->hide();
        ui->debugsaveButton->hide();
        ui->fixlabel->hide();
        ui->fixlabel2->hide();
        ui->timelabel->hide();
        ui->countlabel->hide();
        ui->ontopcheckbox->hide();
        ui->screenlabel->hide();
        ui->methodtab->hide();
        ui->optionButton->hide();
        ui->optionwidget->hide();
        this->resize(100,60);
        this->move(config.position_small);
        //this->move(100,100);
    } else {
        if(config.ontop) set_windowparameters(1);
        else set_windowparameters(0);
        current_small_window = false;
        ui->findButton->show();
        ui->resizeButton->show();
        ui->fixlabel->show();
        ui->countlabel->show();
        ui->ontopcheckbox->show();
        ui->screenlabel->show();
        ui->methodtab->show();
        ui->optionButton->show();
        ui->optionwidget->hide();
        if(config.show_searchtimer) {
            ui->fixlabel2->show();
            ui->timelabel->show();
        }
        else {
            ui->fixlabel2->hide();
            ui->timelabel->hide();
        }
        if(is_debug) {
            ui->pixel_label->hide();
            ui->debugloadButton->show();
            ui->debugsaveButton->show();

        } else {
            ui->notelabel->show();
            ui->debugloadButton->hide();
            ui->debugsaveButton->hide();
        }
        this->resize(config.size);
        this->move(config.position_small);
    }
}

void DsoFinder::set_windowparameters(int value)
{
    //ENABLE/DISABLE ALLWAYS-ON-TOP
    if(value>0 && !current_ontop_windowsetting) { setWindowFlags(Qt::WindowStaysOnTopHint); current_ontop_windowsetting = true; }
    else if(value == 0 && current_ontop_windowsetting){ setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint); current_ontop_windowsetting = false; }
    this->show();
}

void DsoFinder::on_ontopcheckbox_stateChanged(int is_checked)
{
    set_windowparameters(is_checked);
    this->move(config.position_small);
    if(is_checked) config.ontop = true;
    else config.ontop = false;
}

int DsoFinder::get_method()
{
    return ui->methodtab->currentIndex();
}

void DsoFinder::on_methodtab_currentChanged(int index)
{
    if(index==1) {                      //BUILDING-SITE-METHOD
        if(bg_exist==false) {           //INIT METHOD IF BG-PIC IS NOT LOADED
            load_background();
        }
    }
}

void DsoFinder::activate_buttons(bool activate)
{
    ui->bg_editpushButton->setEnabled(activate);
    ui->showbgButton->setEnabled(activate);
    ui->bgdeletepushButton->setEnabled(activate);
}

void DsoFinder::load_background()
{
    // TRY LOADING BACKGROUND
    if(BGImage.load(QString("background%1.png").arg(config.use_bg))==true) {
        bg_exist = true;
    }
    else {
        bg_exist = false;
        if(bg_count == 0) {
            msgbox.setText(QString(tr("No background file found! Create it like this:\na) Open DSO in your max-sized browser.\nb) Make sure there is no collectible left on your map at the moment\nc) Zoom out as far as possible\nd) Move to a fixed position(e.g.: hitting 5 on your keyboard)\ne) Grab a flowerbed or other 1x1 decorational item from you starmenu (Most of the map should apear greenish now)\nf) Open this program, move the window somewhere in your screen where it only hides water\ng) Hit Take Screen\nh) Hit Save as BG\n\n!Redo this everytime you move/erase/build new stuff on your map!")));
            msgbox.exec();
        }
    }
    if(config.use_bg >= bg_count) activate_buttons(false);
    else activate_buttons(true);
}

void DsoFinder::on_bgcomboBox_activated(int index)
{
    config.use_bg = index;
    load_background();
}

void DsoFinder::setactive(bool active)
{
    if(!active) {
        ui->findButton->setText(tr("searching..."));
        ui->countlabel->setText("?");
        ui->findButton->setEnabled(false);
    } else {
        ui->findButton->setText(tr("Find Objects"));
        ui->findButton->setEnabled(true);
    }

    QCoreApplication::processEvents();

}
