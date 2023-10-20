#include "details.h"
#include "ui_details.h"

Details::Details(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Details)
{
    ui->setupUi(this);
    disableField();
    returned = true;
    editingStarted = false;
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
}

Details::~Details()
{
    delete ui;
}

void Details::AcceptData(QString data, int n){
    hideField(n);
    setStrings(data, n);
    incomingDatabase = n;
}

void Details::setStrings(QString data, int n){
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    if(n == 1){
        query.prepare("Select * from bookRegistry where accessionNum = '" + data + "'");
        if(query.exec()){
            while(query.next()){
                accessionNum = query.value(0).toString();
                title = query.value(1).toString();
                author = query.value(2).toString();
                publisher = query.value(3).toString();
                place = query.value(4).toString();
                year = query.value(5).toString();
                source = query.value(6).toString();
                pages = query.value(7).toString();
                edition = query.value(8).toString();
                price = query.value(9).toString();
            }
        }
    }
    else{
        query.prepare("select ledger.borrowId,ledger.accessionNum,bookRegistry.bookTitle,ledger.regNo ,student.name ,ledger.issueDate ,ledger.returnDate,ledger.dueDate  from ledger join bookRegistry on bookRegistry.accessionNum = ledger.accessionNum join student on student.regNo == ledger.regNo where ledger.borrowId = '"+ data +"'");
        if(query.exec()){
            while(query.next()){
                borrowId = query.value(0).toString();
                accessionNum = query.value(1).toString();
                title = query.value(2).toString();
                renNo = query.value(3).toString();
                name = query.value(4).toString();
                issueDate = query.value(5).toString();
                returnDate = query.value(6).toString();
                dueDate = query.value(7).toString();

                bool check = returnDate.toStdString() == "";
                if(check)
                    returned = false;
            }
        }
    }
    FillData(n);
    if(!returned)
        FillData(3);

}

void Details::disableField(){
    ui->input1->setDisabled(true);
    ui->input2->setDisabled(true);
    ui->input3->setDisabled(true);
    ui->input4->setDisabled(true);
    ui->input5->setDisabled(true);
    ui->input6->setDisabled(true);
    ui->input7->setDisabled(true);
    ui->input8->setDisabled(true);
    ui->input9->setDisabled(true);
    ui->input10->setDisabled(true);
    ui->input11->setDisabled(true);
    ui->input12->setDisabled(true);
    ui->input13->setDisabled(true);

    ui->ConfirmReturn->hide();
}

void Details::enableField(){
    ui->input1->setDisabled(false);
    ui->input2->setDisabled(false);
    ui->input3->setDisabled(false);
    ui->input4->setDisabled(false);
    ui->input5->setDisabled(false);
    ui->input6->setDisabled(false);
    ui->input7->setDisabled(false);
    ui->input8->setDisabled(false);
    ui->input9->setDisabled(false);
    ui->input10->setDisabled(false);
    ui->input11->setDisabled(false);
    ui->input12->setDisabled(false);
    ui->input13->setDisabled(false);
}

void Details::FillData(int n){
    if(n == 1){
        ui->input1->setText(accessionNum);
        ui->input2->setText(title);
        ui->input3->setText(author);
        ui->input4->setText(publisher);
        ui->input5->setText(place);
        ui->input6->setText(year);
        ui->input7->setText(edition);
        ui->input8->setText(source);
        ui->input9->setText(pages);
        ui->input10->setText(price);
        ui->input11->setText(name);
        ui->input12->setText(course);
        ui->input13->setText(renNo);
    }
    else if(n == 2){
        ui->label_2->setText("Reg No");
        ui->label_3->setText("Borrow Id");
        ui->label_6->setText("Title");
        ui->label_7->setText("Name");
        ui->label_11->setText("Issue Date");
        ui->label_12->setText("Return Date");

        ui->input1->setText(accessionNum);
        ui->input2->setText(renNo);
        ui->input3->setText(borrowId);
        ui->input6->setText(title);
        ui->input7->setText(name);
        ui->input11->setText(issueDate);
        ui->input12->setText(returnDate);
    }
    else if(n == 3){
        ui->label_12->setText("Due Date");
        ui->input12->setText(dueDate);
        ui->ConfirmReturn->show();
    }
}

void Details::hideField(int n){
    if(n == 1){
        ui->input11->hide();
        ui->input12->hide();
        ui->input13->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->label_13->hide();
    }
    else if(n == 2){
        ui->input4->hide();
        ui->input5->hide();
        ui->input8->hide();
        ui->input9->hide();
        ui->input10->hide();
        ui->input13->hide();

        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_8->hide();
        ui->label_9->hide();
        ui->label_10->hide();
        ui->label_13->hide();
    }
}

void Details::on_Edit_clicked()
{
    if(!editingStarted){
        enableField();
        ui->Edit->setText("Confirm Details");
        editingStarted = true;
    }else{
        updateTables();
    }
}

void Details::updateTables(){
    if(incomingDatabase == 1){

        accessionNum = ui->input1->displayText();
        title = ui->input2->displayText();
        author = ui->input3->displayText();
        publisher = ui->input4->displayText();
        place = ui->input5->displayText();
        year = ui->input6->displayText();
        edition = ui->input7->displayText();
        source = ui->input8->displayText();
        pages = ui->input9->displayText();
        price = ui->input10->displayText();


//        query.prepare("Update table set accessionNum = '" + accessionNum +"','" "" )
    }
}

void Details::on_Exit_clicked()
{
    Details::~Details();
}


void Details::on_ConfirmReturn_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQueryModel *model = new QSqlQueryModel(this);

    query.prepare("select * from ledger where borrowId = '" + borrowId + "' and returnDate = ''");
    if(query.exec())
    {
        model->setQuery(query);
        if(model->rowCount() == 1)
        {
            QString todayIs = QDate::currentDate().toString();
            QMessageBox::information(this,"Success","Book Return Successfully");
            query.prepare(" UPDATE ledger set returnDate = '"+ todayIs +"' where borrowId = '"+ borrowId +"'");
            query.exec();
        }
        else
        {
            QMessageBox::warning(this,"Failed","Error while returning : \nBook is not registered or already returned");
        }
    }
}

