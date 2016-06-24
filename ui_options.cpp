#include "dsofinder.h"
#include "ui_dsofinder.h"

//THIS FILE CONTAINS THE CODE FOR INTERACTING WITH THE SETTINGS-MENU

void DsoFinder::set_optionwindow(bool visible)
{
    if(visible) {
        ui->screenlabel->hide();
        ui->optionwidget->show();
        options_visible = true;
    } else {
        ui->screenlabel->show();
        ui->optionwidget->hide();
        options_visible = false;
    }
}

void DsoFinder::on_optionButton_clicked()
{
    if(!options_visible) {
        set_optionwindow(true);
    } else {
        set_optionwindow(false);
    }
}

void DsoFinder::on_waittime_slider_sliderMoved(int position)
{
    ui->waittime_lineEdit->setText(QString("%1").arg(position));
    config.waittime = position;
}

void DsoFinder::on_waittime_lineEdit_textEdited(const QString &arg1)
{
    if(arg1.toInt() != 0) {
        if(arg1.toInt()>2000) {
            ui->waittime_slider->setSliderPosition(2000);
            ui->waittime_lineEdit->setText(QString("%1").arg(2000));
            config.waittime = 2000;
        }
        ui->waittime_slider->setSliderPosition(arg1.toInt());
        config.waittime = arg1.toInt();
    }
}

void DsoFinder::on_searchtimercheckBox_stateChanged(int is_checked)
{
    if(is_checked) {
        config.show_searchtimer = true;
        ui->fixlabel2->show();
        ui->timelabel->show();
    }
    else {
        config.show_searchtimer = false;
        ui->fixlabel2->hide();
        ui->timelabel->hide();
    }
}

/*void DsoFinder::on_coloralternativecheckBox_stateChanged(int is_checked)
{
    if(is_checked) config.use_alternate_scheme = true;
    else config.use_alternate_scheme = false;
}*/


void DsoFinder::on_colorstandardpushButton_clicked()
{
    config.items_standard_color = QColorDialog::getColor(config.items_standard_color,this);
    ui->colorstandardpushButton->setStyleSheet(QString("border-radius: 10px; background-color: rgb(%1, %2, %3);").arg(config.items_standard_color.red()).arg(config.items_standard_color.green()).arg(config.items_standard_color.blue()));
}

void DsoFinder::on_coloreventpushButton_clicked()
{
    config.items_event_color = QColorDialog::getColor(config.items_event_color,this);
    ui->coloreventpushButton->setStyleSheet(QString("border-radius: 10px; background-color: rgb(%1, %2, %3);").arg(config.items_event_color.red()).arg(config.items_event_color.green()).arg(config.items_event_color.blue()));
}


void DsoFinder::on_itembasiccheckBox_stateChanged(int is_checked)
{
    if(is_checked) config.useitems_basic = true;
    else config.useitems_basic = false;
    init_items();
}

void DsoFinder::on_itemadventurecheckBox_stateChanged(int is_checked)
{
    if(is_checked) config.useitems_adventure = true;
    else config.useitems_adventure = false;
    init_items();
}

void DsoFinder::on_itemeventcomboBox_activated(int index)
{
    config.use_event = index;
    init_items();
}

void DsoFinder::on_halfsizecheckbox_stateChanged(int is_checked)
{
    if(is_checked) config.usehalfsize = true;
    else config.usehalfsize = false;
    init_items();
}

void DsoFinder::on_jumpcheckBox_stateChanged(int is_checked)
{
    if(is_checked) config.jump_position = true;
    else config.jump_position = false;
}

void DsoFinder::on_staybigcheckBox_stateChanged(int is_checked)
{
    if(is_checked) {
        config.stay_big = true;
        ui->waittimegroupbox->setDisabled(true);
    }
    else {
        config.stay_big = false;
        ui->waittimegroupbox->setEnabled(true);
    }
}

