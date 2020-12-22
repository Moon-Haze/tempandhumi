#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    QSettings setting;
    SQL_INIT=false;
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::on_SignUpButton_clicked()
{
    this->setCurrentWidget(this->ui->LogUpPage);
}


void LogWidget::setMainPage(MainPageProxy* mpp){
    this->mw=mpp;
}
void LogWidget::on_backButton_clicked()
{
    this->setCurrentWidget(this->ui->LogInPage);
}

void LogWidget::on_logInButton_clicked()
{
    if(!SQL_INIT){
        SQL_INIT=false;
        db=sqlInit();
    }
    QString id=ui->logInIdlineEdit->text();
    QString pwd=ui->logInPwlineEdit->text();
    if(id!=""&&pwd!=""){
        QSqlQuery query;
        query.prepare("select * from user where uid=? and pwd=?");
        query.bindValue(0,id);
        query.bindValue(1,pwd);
        query.exec();
        if(query.size()){
            db.close();
            this->hide();
            mw->show();
            this->close();
        }else{
            QMessageBox::warning(this,"Warning","The Id or Password is Error.",QMessageBox::Ok);
            ui->logInPwlineEdit->clear();
        }
    } else{
        QMessageBox::warning(this,"Warning","The Id or Password is null.",QMessageBox::Ok);
    }
}


void LogWidget::on_logInIdlineEdit_returnPressed()
{
    this->ui->logInPwlineEdit->setFocus();
}

void LogWidget::on_logInPwlineEdit_returnPressed()
{
    this->ui->logInButton->click();
}

void LogWidget::on_logUpIdlineEdit_returnPressed()
{
    this->ui->logUpPwlineEdit->setFocus();
}

void LogWidget::on_logUpPwlineEdit_returnPressed()
{

    this->ui->logUpRpwlineEdit->setFocus();
}

void LogWidget::on_logUpRpwlineEdit_returnPressed()
{
    this->ui->logUpButton->click();
}

void LogWidget::on_logUpButton_clicked()
{
    if(!SQL_INIT){
        SQL_INIT=false;
        db=sqlInit();
    }
    QString name=ui->logUpIdlineEdit->text();
    QString pwd=ui->logUpPwlineEdit->text();
    QString rpwd=ui->logUpRpwlineEdit->text();
    pwd.contains(' ');
    if(name!=""&&pwd!=""&&rpwd!=""){
        if(pwd==rpwd){
            QSqlQuery query;
            query.prepare("call insert_user(?,?,@outval)");
            query.bindValue(0,name);
            query.bindValue(1,pwd);
            query.exec();
            query.exec("select @outval");
            query.first();
            QString id=query.value(0).toString();
            QMessageBox::information(this,"Sign up","Your Id is "+id,QMessageBox::Ok);
            this->setCurrentWidget(this->ui->LogInPage);
            this->ui->logInIdlineEdit->setText(id);
            this->ui->logInPwlineEdit->setText("");
        } else{
            QMessageBox::warning(this,"Warning","The two passwords are not equal.",QMessageBox::Ok);
            ui->logUpPwlineEdit->setText("");
            ui->logUpRpwlineEdit->setText("");
        }
    } else{
        QMessageBox::warning(this,"Warning","The name or Password is null.",QMessageBox::Ok);
    }
}

void LogWidget::on_pWcheckBox_stateChanged(int arg1)
{
    if(arg1){

    }else{

    }
}

