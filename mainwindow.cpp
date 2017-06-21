#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Point.h"

#include <fstream>
#include <QDebug>
#include <QFileDialog>
#include <string.h>

#include "torc/Architecture.hpp"
#include "torc/Physical.hpp"
#include "torc/Common.hpp"
#include "torc/physical/Instance.hpp"
#include "torc/physical/Design.hpp"
#include "torc/physical/Circuit.hpp"
#include "torc/physical/XilinxPhysicalTypes.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <QMessageBox>
#include <QDateTime>
#include <QProcess>

#include "torc/architecture/TileInfo.hpp"
#include "utils.h"

using namespace std;
using namespace torc::common;
using namespace torc::architecture;
using namespace torc::architecture::xilinx;
using namespace torc;

vector<string> usedFileTiles;
vector<string> usedFileSites;
vector<string> usedSites;
QString pathXdlFile;
QString pathXdlSensor;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&process, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(ExitProcess(int , QProcess::ExitStatus )));
    connect(&process, SIGNAL(started()), this, SLOT(StartProcess()));

    refreshXdlFileTab();
    refreshXdlSensorTab();
}


void MainWindow::ExitProcess(int code, QProcess::ExitStatus exitStatus){

    Utils::MessageOk(this, "Finished", "Process completed", "Ok", QMessageBox::Critical);

}

void MainWindow::StartProcess(){
    qDebug() << "comecou";
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::refreshXdlFileTab(){

    QFile fileXdl(pathXdlFile);

    fstream fsXdlToInsert(pathXdlFile.toUtf8());
    if(!fsXdlToInsert.good()) return;
    physical::XdlImporter importerXdlToInsert;
    importerXdlToInsert(fsXdlToInsert, fileXdl.fileName().toStdString());
    physical::DesignSharedPtr dsgWithOutSensorPtr = importerXdlToInsert.getDesignPtr();

    ui->labelDesign->setText(dsgWithOutSensorPtr->getName().c_str());
    ui->labelDeviceName->setText(dsgWithOutSensorPtr->getDevice().c_str());
    ui->labelNumInstances->setText(QString::number(dsgWithOutSensorPtr->getInstanceCount()));
    ui->labelNumNets->setText(QString::number(dsgWithOutSensorPtr->getNetCount()));

    ui->lwInstances->clear();
    ui->lwSlices->clear();
    usedFileTiles.clear();


    for(physical::Circuit::InstanceSharedPtrIterator it = dsgWithOutSensorPtr->instancesBegin(); it != dsgWithOutSensorPtr->instancesEnd(); it++){
        boost::shared_ptr<physical::Instance> instance = *it;
        ui->lwInstances->addItem(instance->getName().c_str());
        ui->cbInsertXdlInstances->addItem(instance->getName().c_str());
        ui->lwSlices->addItem(instance->getSite().c_str());
        usedFileTiles.push_back(instance->getSite().c_str());
    }

    DirectoryTree directoryTree("/home/rafaelalves/torc-export/src/torc/devices");
    DeviceDesignator designator(dsgWithOutSensorPtr->getDevice().c_str());
    DDB ddb(designator);
}

void MainWindow::refreshXdlSensorTab(){
    ui->cbInsertSensorInstances->clear();
    QFile fileXdl(pathXdlSensor);

    fstream fsXdlToInsert(pathXdlSensor.toUtf8());
    if(!fsXdlToInsert.good()) return;
    physical::XdlImporter importerXdlToInsert;
    importerXdlToInsert(fsXdlToInsert, fileXdl.fileName().toStdString());
    physical::DesignSharedPtr dsgWithOutSensorPtr = importerXdlToInsert.getDesignPtr();

    ui->labelDesignSensor->setText(dsgWithOutSensorPtr->getName().c_str());
    ui->labelDeviceNameSensor->setText(dsgWithOutSensorPtr->getDevice().c_str());
    ui->labelNumInstancesSensor->setText(QString::number(dsgWithOutSensorPtr->getInstanceCount()));
    ui->labelNumNetsSensor->setText(QString::number(dsgWithOutSensorPtr->getNetCount()));

    ui->lwInstancesSensor->clear();
    ui->lwSlicesSensor->clear();

    for(physical::Circuit::InstanceSharedPtrIterator it = dsgWithOutSensorPtr->instancesBegin(); it != dsgWithOutSensorPtr->instancesEnd(); it++){
        boost::shared_ptr<physical::Instance> instance = *it;
        ui->lwInstancesSensor->addItem(instance->getName().c_str());
        ui->cbInsertSensorInstances->addItem(instance->getName().c_str());
        ui->lwSlicesSensor->addItem(instance->getSite().c_str());
    }
}

void MainWindow::on_menuOpenXdl_triggered()
{

    ui->cbInsertXdlInstances->clear();
    QString xdlFilePath = QFileDialog::getOpenFileName(this,tr("Select xdl file"),"/home/rafaelalves/Projetos/Compilados/Aging",tr("Video files (*.xdl)"));
    pathXdlFile = xdlFilePath;

    refreshXdlFileTab();
}

void MainWindow::on_menuOpenXdlSensor_triggered()
{
    ui->cbInsertSensorInstances->clear();
    QString xdlFilePath = QFileDialog::getOpenFileName(this,tr("Select xdl file"),"/home/rafaelalves/Projetos/Compilados/Aging",tr("Xdl files (*.xdl)"));
    QFile fileXdl(xdlFilePath);
    pathXdlSensor = xdlFilePath;
    fstream fsXdlToInsert(xdlFilePath.toUtf8());
    if(!fsXdlToInsert.good()) return;
    physical::XdlImporter importerXdlToInsert;
    importerXdlToInsert(fsXdlToInsert, fileXdl.fileName().toStdString());
    physical::DesignSharedPtr dsgWithOutSensorPtr = importerXdlToInsert.getDesignPtr();

    ui->labelDesignSensor->setText(dsgWithOutSensorPtr->getName().c_str());
    ui->labelDeviceNameSensor->setText(dsgWithOutSensorPtr->getDevice().c_str());
    ui->labelNumInstancesSensor->setText(QString::number(dsgWithOutSensorPtr->getInstanceCount()));
    ui->labelNumNetsSensor->setText(QString::number(dsgWithOutSensorPtr->getNetCount()));

    ui->lwInstancesSensor->clear();
    ui->lwSlicesSensor->clear();

    for(physical::Circuit::InstanceSharedPtrIterator it = dsgWithOutSensorPtr->instancesBegin(); it != dsgWithOutSensorPtr->instancesEnd(); it++){
        boost::shared_ptr<physical::Instance> instance = *it;
        ui->lwInstancesSensor->addItem(instance->getName().c_str());
        ui->cbInsertSensorInstances->addItem(instance->getName().c_str());
        ui->lwSlicesSensor->addItem(instance->getSite().c_str());
    }
}

void MainWindow::on_insertSensor_clicked()
{
    if(pathXdlFile.isEmpty()){
        Utils::MessageOk(this, "Error", "Xdl file source not loaded", "Ok", QMessageBox::Critical);
        return;
    }
    if(pathXdlSensor.isEmpty()){
        Utils::MessageOk(this, "Error", "Xdl Sensor not loaded", "Ok", QMessageBox::Critical);
        return;
    }

    if(ui->cbInsertSensorInstances->currentText().isNull()){
        Utils::MessageOk(this, "Error", "Select a instance", "Ok", QMessageBox::Critical);
        return;
    }

    ui->lwInsertLogs->addItem(QDateTime::currentDateTime().toString("[dd/MM/yyyy hh:mm:ss]") + " Initializing insertion...");
    ui->lwInsertLogs->addItem(QDateTime::currentDateTime().toString("[dd/MM/yyyy hh:mm:ss] ") + ui->cbInsertXdlInstances->currentText() + " -> " +ui->cbInsertSensorInstances->currentText());

    // import xdl to insert SENSOR
    QFile fileXdlToInsert(pathXdlFile);
    fstream fsXdlToInsert(pathXdlFile.toUtf8());;
    if(!fsXdlToInsert.good()) return;
    physical::XdlImporter importerXdlToInsert;
    importerXdlToInsert(fsXdlToInsert, fileXdlToInsert.fileName().toStdString());
    physical::DesignSharedPtr dsgWithOutSensorPtr = importerXdlToInsert.getDesignPtr();

    // import xdl SENSOR
    QFile fileXdlSensor(pathXdlSensor);
    fstream fsXdlSensor(pathXdlSensor.toUtf8());
    if(!fsXdlSensor.good()) return;
    physical::XdlImporter importerXdlSensor;
    importerXdlSensor(fsXdlSensor, fileXdlSensor.fileName().toStdString());
    physical::DesignSharedPtr dsgSensorPtr = importerXdlSensor.getDesignPtr();

    //copying sensor instances
    for(physical::Circuit::InstanceSharedPtrIterator it1 = dsgSensorPtr->instancesBegin(); it1 < dsgSensorPtr->instancesEnd(); it1++){
        dsgWithOutSensorPtr->addInstance(*it1);
    }

    //copying sensor nets and unrouting
    for(physical::Circuit::NetSharedPtrIterator itNet1 = dsgSensorPtr->netsBegin(); itNet1 < dsgSensorPtr->netsEnd(); itNet1++){
        boost::shared_ptr<physical::Net> net = *itNet1;
        net->unroute();
        dsgWithOutSensorPtr->addNet(net);
    }

    //unrouting nets xdl file
    for(physical::Circuit::NetSharedPtrIterator itNet2 = dsgWithOutSensorPtr->netsBegin(); itNet2 < dsgWithOutSensorPtr->netsEnd(); itNet2++){
        boost::shared_ptr<physical::Net> net2 = *itNet2;
        net2->unroute();
        dsgWithOutSensorPtr->addNet(net2);

    }

    boost::shared_ptr<physical::Net> myNet = physical::Factory::newNetPtr(ui->cbInsertXdlInstances->currentText().toStdString() + "-" +ui->cbInsertSensorInstances->currentText().toStdString(), physical::eNetTypeNormal);

    physical::Circuit::InstanceSharedPtrIterator instIn = dsgWithOutSensorPtr->findInstance(ui->cbInsertXdlInstances->currentText().toStdString());
    physical::Circuit::InstanceSharedPtrIterator instOut = dsgSensorPtr->findInstance(ui->cbInsertSensorInstances->currentText().toStdString());

    boost::shared_ptr<physical::InstancePin> pinIn = physical::Factory::newInstancePinPtr(*instIn, "O");
    boost::shared_ptr<physical::InstancePin> pinOut = physical::Factory::newInstancePinPtr(*instOut, "I");

    myNet->addSource(pinIn);
    myNet->addSink(pinOut);
    dsgWithOutSensorPtr->addNet(myNet);

    QString outFileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm");
    fstream xdlExport(outFileName.toStdString() + ".xdl", ios_base::out);
    physical::XdlExporter fileExporter(xdlExport);
    fileExporter(dsgWithOutSensorPtr);


    process.start("/opt/Xilinx/14.7/ISE_DS/ISE/bin/lin64/xdl",
                  QStringList() << "-xdl2ncd" << "/home/rafaelalves/Projetos/Compilados/Aging/" + outFileName + ".xdl" << "/home/rafaelalves/Projetos/Compilados/Aging/" + outFileName + ".ncd");
    process.waitForFinished(-1);
    QString stdout = process.readAllStandardOutput();

    if(stdout.contains("Successfully converted design")){
        Utils::MessageOk(this, "Success", "Successfully converted", "Ok", QMessageBox::Information);
    }


}

