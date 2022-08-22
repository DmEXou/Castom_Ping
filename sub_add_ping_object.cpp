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

bool Sub_Add_Ping_Object::ip_check(std::string& str){ // Проверка на валидность IP адресса.
    if ((str.size() < 7)||(str.size() > 15)) return false;
    if (std::count(str.begin(), str.end(), '.') != 3) return false;
    char prev = 0;
    for (const char& ch : str) {
        if ((prev == ch)&&(ch == 46)) return false;
        prev = ch;
        if (((ch < 48) || (ch > 57)) && (ch != 46)) return false;
    }
    if ((*str.begin() == '.')||(*(str.end() - 1) == '.')) return false;

    //Добавить удвление лишних нулей!!!

    return true;
} //ip_check

void Sub_Add_Ping_Object::on_buttonBox_accepted() //Заполнить базу.
{
    base_ref.push_back(std::make_pair(ui->object_2, ui->object_1));
    for(const auto& pars_line : base_ref){
        std::string tmp = pars_line.second->text().toStdString();
        if(!ip_check(tmp)){
            QMessageBox::warning(this, "Warning", "Incorrect IP");
            base.clear();
            break;
        }
        else{
            base.push_back(std::make_pair(pars_line.first->text(), QString::fromStdString (tmp)));
        }
    }
}

void Sub_Add_Ping_Object::on_add_new_lineedit_clicked()//Реакция на ADD в дочернем окне.
{
    QLineEdit *line_name = new QLineEdit(this);
    QLineEdit *line_ip = new QLineEdit(this);
    if (base_ref.size() <= 5 ){
        ui->fild_ip->addWidget(line_ip);
        ui->fild_name->addWidget(line_name);
        base_ref.push_back(std::make_pair(line_name, line_ip));

        ui->fild_ip->addStretch();
        delete ui->fild_ip->takeAt(ui->fild_ip->count() - 3);
        ui->fild_name->addStretch();
        delete ui->fild_name->takeAt(ui->fild_name->count() - 3);
    }
    else{
        QMessageBox::warning(this, "Warning", "Maximum lines");
    }

}


void Sub_Add_Ping_Object::on_del_lineedit_clicked() //Реакция на Del в дочернем окне.
{
    if (base_ref.size() != 0){
        qDebug() << ui->fild_ip->count();
        ui->fild_ip->removeWidget(base_ref.back().second);
        ui->fild_name->removeWidget(base_ref.back().second);
        delete base_ref.back().second;
        delete base_ref.back().first;
        base_ref.pop_back();
    }
    else{
        QMessageBox::warning(this, "Warning", "Minimum lines");
    }
}


void Sub_Add_Ping_Object::on_buttonBox_clicked(QAbstractButton *button) // Не нужно удалить!!!
{

}

