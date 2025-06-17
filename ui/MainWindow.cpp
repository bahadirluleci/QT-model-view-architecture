#include "MainWindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QFrame>

#include "ProductObject.h"
#include "ProductTableWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(std::make_unique<Ui::MainWindow>()),
    productJsonObject(new ProductObject(this)),
    productTableWidget(new ProductTableWidget(this))
{
    ui->setupUi(this);

    createTabs();
}


void MainWindow::createTabs()
{
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    tabWidget->setObjectName("CentralTab");

    // Tab 1: Load and Save
    QFrame* frame = new QFrame(this);
    mainLayout = new QVBoxLayout();
    frame->setLayout(mainLayout);

    auto* browseButton = new QPushButton("Browse...", this);
    auto* loadButton = new QPushButton("Load...", this);
    auto* saveButton = new QPushButton("Save...", this);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    mainLayout->addWidget(browseButton);
    mainLayout->addWidget(loadButton);
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(saveButton);

    tabWidgets.push_back(frame);
    tabWidget->insertTab(Tabs::LoadAndSavePage, tabWidgets[Tabs::LoadAndSavePage], "Load and Save");

    // Second tab: Table
    tabWidgets.push_back(productTableWidget);
    tabWidget->insertTab(Tabs::TableWidgetPage, tabWidgets[Tabs::TableWidgetPage], "Product Table");

    // button connections
    connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
}

void MainWindow::onBrowseClicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open Configuration File"),
                                            QDir::homePath(), tr("JSON Files (*.json)"));
}


void MainWindow::onLoadClicked()
{
    if (filePath.isEmpty() || !productJsonObject)
        return;

    productJsonObject->load(filePath);

    QJsonDocument doc(productJsonObject->getProductObject());
    textEdit->setText(doc.toJson());


    if (productTableWidget)
        productTableWidget->setData(productJsonObject->getProductObject());

    filePath.clear();

}

void MainWindow::onSaveClicked()
{
    if (!productTableWidget)
        return;

    QString savePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    QDir::homePath(), tr("JSON Files (*.json)"));

    if (savePath.isEmpty())
        return;

    QFile file(savePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Unable to open file for writing.";
        return;
    }

    QJsonDocument doc(productTableWidget->data());
    file.write(doc.toJson());
    file.close();
}
