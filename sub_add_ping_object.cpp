#include "sub_add_ping_object.h"
#include "ui_sub_add_ping_object.h"

Sub_Add_Ping_Object::Sub_Add_Ping_Object(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sub_Add_Ping_Object)
{
    ui->setupUi(this);
}

Sub_Add_Ping_Object::~Sub_Add_Ping_Object()
{
    delete ui;
}

void Sub_Add_Ping_Object::on_buttonBox_accepted() //Заполнить базу.
{
    base_ref.push_back(std::make_pair(ui->object_2, ui->object_1));
    for(const auto& pars_line : base_ref){

        base.push_back(std::make_pair(pars_line.first->text(), pars_line.second->text()));
    }
}

void Sub_Add_Ping_Object::on_add_new_lineedit_clicked()//Реакция на ADD в дочернем окне.
{
    QLineEdit *line_name = new QLineEdit(this);
    QLineEdit *line_ip = new QLineEdit(this);

    if (count_line_e <= 5 ){
        count_line_e++;
        ui->fild_ip->addWidget(line_ip);
        ui->fild_name->addWidget(line_name);
        base_ref.push_back(std::make_pair(line_name, line_ip));
    }
    else{
        QMessageBox::warning(this,"Warning" ,"Maximum lines");
    }
}


void Sub_Add_Ping_Object::on_del_lineedit_clicked() //Реакция на Del в дочернем окне.
{

}

