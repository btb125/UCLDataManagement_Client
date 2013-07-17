#include "ViewMainScreen.h"
#include "ui_ViewMainScreen.h"

ViewMainScreen::ViewMainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewMainScreen)
{
    ui->setupUi(this);

    viewDidLoad() ;
}

ViewMainScreen::~ViewMainScreen()
{
    delete ui;
}

void ViewMainScreen::viewDidLoad()
{
    initObjects() ;

    initGUI() ;

    connectSignalsAndSlots() ;

    hideSecondaryMenuButtons() ;
    hideTertiaryMenuButtons() ;

    //PRESENT LOCK SCREEN
    showFrameLockScreen(true) ;

    //PRESENT LOGIN SCREEN
    showFrameLoginScreen(true) ;
}

void ViewMainScreen::initObjects()
{
    userLoggedIn = false ;

    userIsEditingNotAddingObject = false ;

    setNetworkConection() ;

    TITLE_HEIGHT = 30 ;

    MAIN_MENU_PADDING = 5;

    PRIMARY_BUTTON_WIDTH = 120 ;
    PRIMARY_BUTTON_HEIGHT = 70 ;
    PRIMARY_BUTTON_GRADIENT = 20 ;

    SECONDARY_BUTTON_WIDTH = 100 ;
    SECONDARY_BUTTON_HEIGHT = 70 ;
    SECONDARY_BUTTON_GRADIENT = 20 ;

    LOGIN_FRAME_WIDTH = 320 ;
    LOGIN_FRAME_HEIGHT = 320 ;
}

void ViewMainScreen::initGUI()
{
    initFrame_MainWorkingArea() ;

    initButtons_TertiaryButtons() ;
    initButtons_SecondaryButtons() ;
    initButtons_PrimaryButtons() ;

    initFrame_LockScreen() ;
    initFrame_LoginScreen() ;
}

void ViewMainScreen::connectSignalsAndSlots()
{
    /*
     * Login
     */
    connect(lineEdit_Login_Username, SIGNAL(returnPressed()), pushButton_Login_Login, SIGNAL(clicked())) ;
    connect(lineEdit_Login_Password, SIGNAL(returnPressed()), pushButton_Login_Login, SIGNAL(clicked())) ;
    connect(pushButton_Login_Login, SIGNAL(clicked()), this, SLOT(pushButton_Login_Login_clicked())) ;

    /*
     * Home
     */
    connect(pushButton_Menu_Primary_Button_Home, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Primary_Button_Home_clicked())) ,

    /*
     * Research
     */

    /*
     * Questionnaires & Questions
     */
    //Main
    connect(pushButton_Menu_Primary_Button_Questionnaires, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Primary_Button_Questionnaires_clicked())) ;

    //Secondary
    connect(pushButton_Menu_Secondary_Button_Questionnaires, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Secondary_Button_Questionnaires_clicked())) ;
    connect(pushButton_Menu_Secondary_Button_Questions, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Secondary_Button_Questions_clicked())) ;

    //Tertiary
    connect(pushButton_Menu_Tertiary_Button_Questionnaire_View, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Questionnaire_View_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Questionnaire_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Questionnaire_Add_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Questionnaire_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Questionnaire_Edit_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Questionnaire_Remove, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Questionnaire_Remove_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Questions_View, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Questions_View_clicked())) ;

    //AddEdit
    connect(pushButton_Questionnaires_View_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Questionnaires_View_Add_clicked())) ;
    connect(pushButton_Questionnaires_View_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Questionnaires_View_Edit_clicked())) ;
    connect(pushButton_Questionnaires_View_Delete, SIGNAL(clicked()),
            this, SLOT(pushButton_Questionnaires_View_Delete_clicked())) ;
    connect(pushButton_Questionnaires_AddEdit_Submit, SIGNAL(clicked()),
            this, SLOT(pushButton_Questionnaires_AddEdit_Submit_clicked())) ;

    connect(comboBox_Questionnaires_AddEdit_New_Question_Question_Type, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(comboBox_Questionnaires_AddEdit_New_Question_Question_Type_clicked(QString))) ;
    connect(pushButton_Questionnaires_AddEdit_AddLine, SIGNAL(clicked()),
            this, SLOT(pushButton_Questionnaires_AddEdit_AddLine_clicked())) ;

    //Tables
    connect(tableWidget_Questionnaires_View, SIGNAL(clicked(QModelIndex)),
            this, SLOT(tableWidget_Questionnaires_View_Cell_clicked(QModelIndex))) ;

    //Signal Mapper
    connect(signalMapperQuestionnaireAddEdit, SIGNAL(mapped(QString)),
            this, SIGNAL(clicked(QString))) ;

    connect(this, SIGNAL(clicked(QString)),
            this, SLOT(pushButton_Questionnaires_AddEdit_Remove_Question_clicked(QString))) ;

    /*
     * Participants
     */
    //Main
    connect(pushButton_Menu_Primary_Button_Participants, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Primary_Button_Participants_clicked())) ;

    //Secondary
    connect(pushButton_Menu_Secondary_Button_Participants, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Secondary_Button_Participants_clicked())) ;
    //Tertiary
    connect(pushButton_Menu_Tertiary_Button_Participants_View, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Participants_View_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Participants_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Participants_Add_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Participants_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Participants_Edit_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_Participants_Remove, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Button_Participants_Remove_clicked())) ;

    //Participants AddEdit
    connect(pushButton_Participants_View_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Participants_View_Add_clicked())) ;
    connect(pushButton_Participants_View_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Participants_View_Edit_clicked())) ;
    connect(pushButton_Participants_View_Delete, SIGNAL(clicked()),
            this, SLOT(pushButton_Participants_View_Delete_clicked())) ;
    connect(pushButton_Participants_AddEdit_Submit, SIGNAL(clicked()),
            this, SLOT(pushButton_Participants_AddEdit_Submit_clicked())) ;

    //Participants Table
    connect(tableWidget_Participants_View, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(tableWidget_Participants_View_Cell_clicked(const QModelIndex &))) ;

    /*
     * Settings
     */
    //Main
    connect(pushButton_Menu_Primary_Button_Settings, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Primary_Button_Settings_clicked())) ;

    //Secondary
    connect(pushButton_Menu_Secondary_Buttons_Settings_APLs, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Secondary_Buttons_Settings_APLs_clicked())) ;
    connect(pushButton_Menu_Secondary_Buttons_Settings_Users, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Secondary_Buttons_Settings_Users_clicked())) ;

    //Tertiary
    connect(pushButton_Menu_Tertiary_Button_APL_View, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_APLs_View_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_APL_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_APLs_Add_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_APL_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_APLs_Edit_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_APL_Remove, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_APLs_Delete_clicked())) ;

    connect(pushButton_Menu_Tertiary_Button_User_View, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_Users_View_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_User_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_Users_Add_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_User_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_Users_Edit_clicked())) ;
    connect(pushButton_Menu_Tertiary_Button_User_Remove, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Tertiary_Buttons_Settings_Users_Delete_clicked())) ;

    //Tables
    connect(tableWidget_Users_View, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(tableWidget_Users_View_Cell_clicked(const QModelIndex &))) ;
    connect(tableWidget_APLs_View, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(tableWidget_ALPs_View_Cell_clicked(const QModelIndex &))) ;

    //Users AddEdit
    connect(pushButton_Users_View_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_Users_View_Add_clicked())) ;
    connect(pushButton_Users_View_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_Users_View_Edit_clicked())) ;
    connect(pushButton_Users_View_Delete, SIGNAL(clicked()),
            this, SLOT(pushButton_Users_View_Delete_clicked())) ;
    connect(pushButton_Users_AddEdit_Submit, SIGNAL(clicked()),
            this, SLOT(pushButton_Users_AddEdit_Submit_clicked())) ;

    //APLs AddEdit
    connect(pushButton_APLs_View_Add, SIGNAL(clicked()),
            this, SLOT(pushButton_APLs_View_Add_clicked())) ;
    connect(pushButton_APLs_View_Edit, SIGNAL(clicked()),
            this, SLOT(pushButton_APLs_View_Edit_clicked())) ;
    connect(pushButton_APLs_View_Delete, SIGNAL(clicked()),
            this, SLOT(pushButton_APLs_View_Delete_clicked())) ;
    connect(pushButton_APLs_AddEdit_Submit, SIGNAL(clicked()),
            this, SLOT(pushButton_APLs_AddEdit_Submit_clicked())) ;

    /*
     * Collaboration & Back-Up
     */

    /*
     * Lock
     */
    connect(pushButton_Menu_Primary_Button_Lock, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Primary_Button_Lock_clicked())) ;

    /*
     * Logout
     */
    connect(pushButton_Menu_Primary_Button_Logout, SIGNAL(clicked()),
            this, SLOT(pushButton_Menu_Primary_Button_Logout_clicked())) ;
}

void ViewMainScreen::setNetworkConection()
{
    socket = new QTcpSocket(this) ;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead())) ;
}

void ViewMainScreen::readyRead()
{
    incomingMessage = socket->readAll() ;
    connection.read(incomingMessage.toStdString()) ;

    if (connection.getInboundHeader() == "user    ")
    {
        loginSuccessful(connection.readUser()) ;
    }

    if (connection.getInboundHeader() == "logifail")
    {
        loginFailed() ;
    }

    if (connection.getInboundHeader() == "ret*Usrs")
    {
        users = connection.readUsers() ;

        updateUserTableWidget() ;

        showWidgetInMainWorkingStackedWidget(widget_Users_View) ;
    }

    if (this->connection.getInboundHeader() == "ret*APLs" )
    {
        accessPermissionLists = connection.readAccessPermissionLists() ;

        updateAPLTableWidget() ;

        showWidgetInMainWorkingStackedWidget(widget_APLs_View) ;
    }

    if (this->connection.getInboundHeader() == "ret*Ppts")
    {
        participants = connection.readParticipants() ;

        updateParticipantTableWidget() ;

        showWidgetInMainWorkingStackedWidget(widget_Participants_View) ;
    }

    if (this->connection.getInboundHeader() == "ret*Ques")
    {
        questionnaires = connection.readQuestionnaires() ;

        updateQuestionnaireTableWidget() ;

        showWidgetInMainWorkingStackedWidget(widget_Questionnaires_View) ;
    }

    if (this->connection.getInboundHeader() == "updMsg  ")
    {
        if (this->connection.getInboundMessage() == "APL" )
        {
            getAllAccessPermissionLists() ;
        }

        if (this->connection.getInboundMessage() == "User" )
        {
            getAllUsers() ;
        }

        if (this->connection.getInboundMessage() == "Participant")
        {
            getAllParticipants() ;
        }

        if (this->connection.getInboundMessage() == "Questionnaire")
        {
            getAllQuestionnaires() ;
        }
    }

    if (this->connection.getInboundHeader() == "retMsg  ")
    {
        QMessageBox::warning(this,
                             "Warning",
                             QString::fromStdString(connection.getInboundMessage()),
                             QMessageBox::Ok) ;
    }
}

void ViewMainScreen::readyWrite()
{
    //Clear & Set Write Buffer
    buffer.clear() ;
    buffer.append(QString::fromStdString(connection.write())) ;

    //Clear & Set Socket to Write to
    socket->abort();
    socket->connectToHost(QString::fromStdString(ServerInformation::getInstance()->getIPAddress()),
                          ServerInformation::getInstance()->getPort()) ;

    //Write Buffer to Socket
    socket->write(buffer) ;
}

void ViewMainScreen::updateUserTableWidget()
{
    QStringList tableHeaders ;
    tableHeaders << "ID" << "Forename" << "Surname" << "Department" << "Role" << "APL" << "Account Active?" ;

    const int COLUMN_COUNT = tableHeaders.size() ;
    tableWidget_Users_View->setColumnCount(COLUMN_COUNT);
    tableWidget_Users_View->setRowCount(users.size());

    tableWidget_Users_View->setHorizontalHeaderLabels(tableHeaders) ;

    User user ;
    user = users.at(0) ;

    for (unsigned row = 0; row < users.size(); row++)
    {
        user = users.at(row) ;

        tableWidget_Users_View->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(
                                                                        user.getUserId()))) ;
        tableWidget_Users_View->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(
                                                                        user.getForename()))) ;
        tableWidget_Users_View->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(
                                                                        user.getSurname()))) ;
        tableWidget_Users_View->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(
                                                                        user.getDepartment()))) ;
        tableWidget_Users_View->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(
                                                                        user.getRole()))) ;
        tableWidget_Users_View->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(
                                                                        user.getAccessPermissionList()
                                                                            .getName()))) ;
        if (user.getIsAccountActive())
        {
            tableWidget_Users_View->setItem(row, 6, new QTableWidgetItem("Yes")) ;
        }
        else
        {
            tableWidget_Users_View->setItem(row, 6, new QTableWidgetItem("No")) ;
        }
    }
}

void ViewMainScreen::getAllUsers()
{
    connection.setOutboundHeader("get*Usrs") ;
    readyWrite() ;
}

void ViewMainScreen::viewUserTableWidget()
{
    getAllUsers(); ;
}

void ViewMainScreen::viewAddEditUser()
{
    loadUserAddEditAccessPermissionListComboBox() ;

    if (!userIsEditingNotAddingObject)
    {
        lineEdit_Users_AddEdit_Forename->setText("") ;
        lineEdit_Users_AddEdit_Surname->setText("") ;
        lineEdit_Users_AddEdit_Department->setText("") ;
        lineEdit_Users_AddEdit_Role->setText("") ;
        checkBox_Users_AddEdit_AccountActive->setChecked(true) ;

        pushButton_Users_AddEdit_Submit->setText("Add") ;

        //Generate New & Unused Username
        QString username ;
        bool unusedUsername = false ;//WARNING
        User user ;

        while (!unusedUsername)
        {
            username = generateRandomUsername() ;

            for (unsigned i = 0; i < users.size(); i++)
            {
                user = users.at(i) ;

                if (username != QString::fromStdString(user.getUserId()))
                {
                    unusedUsername = true ;
                }
            }
        }

        label_Users_AddEdit_UserID_Generated_ID->setText(username) ;
    }
    else
    {
        //Get Selected Row
        QItemSelectionModel *selectedModel = tableWidget_Users_View->selectionModel() ;
        QModelIndexList indexOfRows = selectedModel->selectedRows() ;

        User userToBeEditted = users.at(indexOfRows.at(0).row()) ;

        label_Users_AddEdit_UserID_Generated_ID->setText(QString::fromStdString(userToBeEditted.getUserId())) ;
        label_Users_AddEdit_Password_Default_Password->setText("********") ;
        lineEdit_Users_AddEdit_Forename->setText(QString::fromStdString(userToBeEditted.getForename())) ;
        lineEdit_Users_AddEdit_Surname->setText(QString::fromStdString(userToBeEditted.getSurname())) ;
        lineEdit_Users_AddEdit_Department->setText(QString::fromStdString(userToBeEditted.getDepartment())) ;
        lineEdit_Users_AddEdit_Role->setText(QString::fromStdString(userToBeEditted.getRole())) ;
    }

    showWidgetInMainWorkingStackedWidget(widget_Users_AddEdit) ;
}

QString ViewMainScreen::generateRandomUsername()
{
    QString randomUsername ;
    randomUsername = "ucl" ;

    int randomNumber ;
    randomNumber = rand() % 1000 + 1 ;

    //Ensure A Correct Number is Generated
    while (!(randomNumber > 1) && !(randomNumber < 1000))
    {
        randomNumber = rand() % 1000 + 1 ;
    }

    //Ensure 3 figure length
    if (randomNumber < 10)
    {
        randomUsername.append("00") ;
    }
    else if (randomNumber < 100 && randomNumber > 10)
    {
        randomUsername.append("0") ;
    }

    randomUsername.append(QString::number(randomNumber)) ;
    randomUsername.append("    ") ;

    return randomUsername ;
}

void ViewMainScreen::loadUserAddEditAccessPermissionListComboBox()
{


    comboBox_Users_AddEdit_APL->clear() ;

    AccessPermissionList apl ;
    for (unsigned i = 0; i < accessPermissionLists.size(); i++)
    {
        apl = accessPermissionLists.at(i) ;

        comboBox_Users_AddEdit_APL->addItem(QString::fromStdString(apl.getName()));
    }
}

void ViewMainScreen::deleteUser()
{
    //Prepare Data to be written to Socket
    this->connection.setOutboundHeader("delxUsrs") ;

    //Get Selected Rows
    QItemSelectionModel *selectedModel = tableWidget_Users_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    //Vector Array of APLs To Be Deleted
    std::vector<User> usersToBeDeleted ;

    //Get All APLs To Be Deleted From Rows
    for (int i = 0; i < indexOfRows.size(); i++)
    {
        usersToBeDeleted.push_back(users.at(indexOfRows.at(i).row())) ;
    }

    connection.setOutboundMessage(usersToBeDeleted) ;

    //Write to Socket
    readyWrite() ;
}

void ViewMainScreen::hideSecondaryMenuButtons()
{
    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Settings.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Settings.at(i)->hide() ;
    }

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Participants.at(i)->hide() ;
    }

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Questionnaires.at(i)->hide() ;
    }
}

void ViewMainScreen::hideTertiaryMenuButtons()
{
    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Settings_APLs.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Settings_APLs.at(i)->hide() ;
    }

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Settings_Users.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Settings_Users.at(i)->hide() ;
    }

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Participants.at(i)->hide() ;
    }

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Questionnaires.at(i)->hide() ;
    }

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Questions.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Questions.at(i)->hide() ;
    }
}

void ViewMainScreen::showMenuSecondaryButtonsSettings()
{
    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Settings.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Settings.at(i)->show() ;
    }
}

void ViewMainScreen::showMenuSecondaryButtonsQuestionnaires()
{
    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Questionnaires.at(i)->show() ;
    }
}

void ViewMainScreen::showMenuTertiaryButtonsAPLs()
{
    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Settings_APLs.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Settings_APLs.at(i)->show() ;
    }

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Settings_Users.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Settings_Users.at(i)->show() ;
    }
}

void ViewMainScreen::showMenuTertiaryButtonsParticipants()
{
    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Participants.at(i)->show() ;
    }
}

void ViewMainScreen::showMenuSecondaryButtonsParticipants()
{
    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Participants.at(i)->show() ;
    }
}

void ViewMainScreen::initFrame_MainWorkingArea()
{
    /*
     * Title
     */
    label_Window_Title = new QLabel("Welcome", this) ;
    label_Window_Title->setGeometry((MAIN_MENU_PADDING + PRIMARY_BUTTON_WIDTH + (SECONDARY_BUTTON_WIDTH*2) - (PRIMARY_BUTTON_GRADIENT*2) + (MAIN_MENU_PADDING*4)), MAIN_MENU_PADDING,
            500, TITLE_HEIGHT) ;
    QFont f( "Verdana", 24, QFont::Normal) ;
    label_Window_Title->setFont(f) ;

    /*
     * Frame
     */
    frame_MainWorkingAreaBorder = new QFrame(this) ;
    frame_MainWorkingAreaBorder->setGeometry((MAIN_MENU_PADDING + PRIMARY_BUTTON_WIDTH + SECONDARY_BUTTON_WIDTH - PRIMARY_BUTTON_GRADIENT + SECONDARY_BUTTON_WIDTH - SECONDARY_BUTTON_GRADIENT + (MAIN_MENU_PADDING*4)),
                                       (MAIN_MENU_PADDING + TITLE_HEIGHT + (MAIN_MENU_PADDING*4)),
                                       (this->geometry().width() - MAIN_MENU_PADDING - PRIMARY_BUTTON_WIDTH + PRIMARY_BUTTON_GRADIENT - SECONDARY_BUTTON_WIDTH + SECONDARY_BUTTON_GRADIENT - SECONDARY_BUTTON_WIDTH + SECONDARY_BUTTON_GRADIENT - ((MAIN_MENU_PADDING*4)*3)),
                                       (this->geometry().height() - MAIN_MENU_PADDING - TITLE_HEIGHT - ((MAIN_MENU_PADDING*4)*2))) ;
    frame_MainWorkingAreaBorder->setStyleSheet("QFrame { background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #83FF83, stop:1 #00A3CC); border-top-right-radius:20px ; border-bottom-right-radius:20px ; border-top-left-radius:20px ; border-bottom-left-radius:20px ;}") ;

    frame_MainWorkingAreaBorder->show() ;

    frame_MainWorkingArea = new QFrame(frame_MainWorkingAreaBorder) ;
    frame_MainWorkingArea->setGeometry((MAIN_MENU_PADDING*4),(MAIN_MENU_PADDING*4),
                                       (frame_MainWorkingAreaBorder->width()-((MAIN_MENU_PADDING*4)*2)),
                                       (frame_MainWorkingAreaBorder->height()-((MAIN_MENU_PADDING*4)*2))) ;
    frame_MainWorkingArea->setStyleSheet("QFrame { background-color: white ; }") ;
    frame_MainWorkingArea->show() ;

    /*
     * Home
     */
    widget_Home = new QWidget() ;
    layout_Vertical_Home  = new QVBoxLayout() ;
    layout_Horizontal_Home = new QHBoxLayout() ;

    layout_Vertical_Home->addLayout(layout_Horizontal_Home) ;

    widget_Home->setLayout(layout_Vertical_Home) ;

    /*
     * Users Table View
     */
    widget_Users_View = new QWidget() ;
    layout_Vertical_Users_View = new QVBoxLayout() ;
    layout_Horizontal_Users_View = new QHBoxLayout() ;

    tableWidget_Users_View = new QTableWidget(widget_Users_View) ;
    tableWidget_Users_View->setEditTriggers(QAbstractItemView::NoEditTriggers) ;

    pushButton_Users_View_Add = new QPushButton("Add", widget_Users_View) ;
    pushButton_Users_View_Edit = new QPushButton("Edit", widget_Users_View) ;
    pushButton_Users_View_Delete = new QPushButton("Delete", widget_Users_View) ;

    layout_Horizontal_Users_View->addWidget(pushButton_Users_View_Add) ;
    layout_Horizontal_Users_View->addWidget(pushButton_Users_View_Edit) ;
    layout_Horizontal_Users_View->addWidget(pushButton_Users_View_Delete) ;

    layout_Vertical_Users_View->addWidget(tableWidget_Users_View) ;
    layout_Vertical_Users_View->addLayout(layout_Horizontal_Users_View) ;

    widget_Users_View->setLayout(layout_Vertical_Users_View) ;

    /*
     * Users Add/Edit
     */
    //Widget - Users Add/Edit
    widget_Users_AddEdit = new QWidget() ;
    layout_Vertical_Users_AddEdit = new QVBoxLayout() ;
    layout_Horizontal_Users_AddEdit = new QHBoxLayout() ;
    layout_Form_Users_AddEdit_Form = new QFormLayout() ;

    label_Users_AddEdit_UserID = new QLabel("* User ID:", widget_Users_AddEdit) ;
    label_Users_AddEdit_UserID_Generated_ID = new QLabel("Please wait...", widget_Users_AddEdit) ;

    label_Users_AddEdit_Password = new QLabel("* Password:", widget_Users_AddEdit) ;
    label_Users_AddEdit_Password_Default_Password = new QLabel("Password1", widget_Users_AddEdit) ;

    label_Users_AddEdit_Forename = new QLabel("* Forename:", widget_Users_AddEdit) ;
    lineEdit_Users_AddEdit_Forename = new QLineEdit(widget_Users_AddEdit) ;

    label_Users_AddEdit_Surname = new QLabel("* Surname:", widget_Users_AddEdit) ;
    lineEdit_Users_AddEdit_Surname = new QLineEdit(widget_Users_AddEdit) ;


    label_Users_AddEdit_Department = new QLabel("* Department:", widget_Users_AddEdit) ;
    lineEdit_Users_AddEdit_Department = new QLineEdit(widget_Users_AddEdit) ;

    label_Users_AddEdit_Role = new QLabel("* Role:", widget_Users_AddEdit) ;
    lineEdit_Users_AddEdit_Role = new QLineEdit(widget_Users_AddEdit) ;

    label_Users_AddEdit_APL = new QLabel("* APL:", widget_Users_AddEdit) ;
    comboBox_Users_AddEdit_APL = new QComboBox(widget_Users_AddEdit) ;

    label_Users_AddEdit_AccountActive = new QLabel("* Account Active?:", widget_Users_AddEdit) ;
    checkBox_Users_AddEdit_AccountActive = new QCheckBox(widget_Users_AddEdit) ;
    checkBox_Users_AddEdit_AccountActive->setChecked(true) ;

    pushButton_Users_AddEdit_Submit = new QPushButton("Submit", widget_Users_AddEdit) ;

    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_UserID, label_Users_AddEdit_UserID_Generated_ID) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_Password, label_Users_AddEdit_Password_Default_Password) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_Forename, lineEdit_Users_AddEdit_Forename) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_Surname, lineEdit_Users_AddEdit_Surname) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_Department, lineEdit_Users_AddEdit_Department) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_Role, lineEdit_Users_AddEdit_Role) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_APL, comboBox_Users_AddEdit_APL) ;
    layout_Form_Users_AddEdit_Form->addRow(label_Users_AddEdit_AccountActive, checkBox_Users_AddEdit_AccountActive) ;

    layout_Horizontal_Users_AddEdit_Buttons = new QHBoxLayout() ;
    layout_Horizontal_Users_AddEdit_Buttons->addWidget(pushButton_Users_AddEdit_Submit);

    layout_Horizontal_Users_AddEdit->addLayout(layout_Form_Users_AddEdit_Form) ;

    layout_Vertical_Users_AddEdit->addLayout(layout_Horizontal_Users_AddEdit) ;
    layout_Vertical_Users_AddEdit->addLayout(layout_Horizontal_Users_AddEdit_Buttons) ;

    widget_Users_AddEdit->setLayout(layout_Vertical_Users_AddEdit) ;

    /*
     * APLs Table View
     */
    widget_APLs_View = new QWidget() ;
    layout_Vertical_APLs_View = new QVBoxLayout() ;
    layout_Horizontal_APLs_View = new QHBoxLayout() ;

    tableWidget_APLs_View = new QTableWidget(1, 1, widget_APLs_View) ;
    tableWidget_APLs_View->setEditTriggers(QAbstractItemView::NoEditTriggers) ;

    pushButton_APLs_View_Add = new QPushButton("Add", widget_APLs_View) ;
    pushButton_APLs_View_Edit = new QPushButton("Edit", widget_APLs_View) ;
    pushButton_APLs_View_Delete = new QPushButton("Delete", widget_APLs_View) ;

    layout_Horizontal_APLs_View->addWidget(pushButton_APLs_View_Add) ;
    layout_Horizontal_APLs_View->addWidget(pushButton_APLs_View_Edit) ;
    layout_Horizontal_APLs_View->addWidget(pushButton_APLs_View_Delete) ;

    layout_Vertical_APLs_View->addWidget(tableWidget_APLs_View) ;
    layout_Vertical_APLs_View->addLayout(layout_Horizontal_APLs_View) ;

    widget_APLs_View->setLayout(layout_Vertical_APLs_View) ;

    /*
     * APLs Add/Edit
     */
    widget_APLs_AddEdit = new QWidget() ;
    layout_APLs_AddEdit = new QVBoxLayout() ;
    layout_APLs_AddEdit_TitleActive = new QHBoxLayout() ;
    layout_APLs_AddEdit_Title = new QHBoxLayout() ;
    layout_APLs_AddEdit_Active = new QHBoxLayout() ;
    layout_APLs_AddEdit_CheckBoxes = new QHBoxLayout() ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA = new QVBoxLayout() ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB = new QVBoxLayout() ;
    layout_APLs_AddEdit_Button = new QHBoxLayout() ;

    label_APLs_AddEdit_Name = new QLabel("APL Name:", widget_APLs_AddEdit) ;
    lineEdit_APLs_AddEdit_Name = new QLineEdit(widget_APLs_AddEdit) ;

    checkBox_APLs_AddEdit_Active = new QCheckBox("APL Active?", widget_APLs_AddEdit) ;

    label_APLs_AddEdit_Research_Topics = new QLabel("<b>Research Topics</b>", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Research_Topics_View = new QCheckBox("View Research Topics", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Research_Topics_Add = new QCheckBox("Add Research Topics", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Research_Topics_Edit = new QCheckBox("Edit Research Topics", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Research_Topics_Delete = new QCheckBox("Delete Research Topics", widget_APLs_AddEdit) ;

    label_APLs_AddEdit_Participants = new QLabel("<b>Participants</b", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Participants_View = new QCheckBox("View Participants", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Participants_Add = new QCheckBox("Add Participants", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Participants_Edit = new QCheckBox("Edit Participants", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Participants_Delete = new QCheckBox("Delete Participants", widget_APLs_AddEdit) ;

    label_APLs_AddEdit_Questionnaires= new QLabel("<b>Questionnaires</b>", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Questionnaires_View = new QCheckBox("View Questionnaires", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Questionnaires_Add = new QCheckBox("Add Questionnaires", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Questionnaires_Edit = new QCheckBox("Edit Questionnaires", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Questionnaires_Delete = new QCheckBox("Delete Questionnaires", widget_APLs_AddEdit) ;

    label_APLs_AddEdit_Users = new QLabel("<b>Users</b>", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Users_View = new QCheckBox("View Users", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Users_Add = new QCheckBox("Add Users", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Users_Edit = new QCheckBox("Edit Users", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Users_Delete = new QCheckBox("Delete Users", widget_APLs_AddEdit) ;

    label_APLs_AddEdit_Other = new QLabel("<b>Other</b>", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_SearchDatabase = new QCheckBox("Search Database", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_BackUp = new QCheckBox("Back Up", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Collaborate = new QCheckBox("Collaborate", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Export = new QCheckBox("Export", widget_APLs_AddEdit) ;

    label_APLs_AddEdit_Settings = new QLabel("<b>Settings</b>", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Settings_View = new QCheckBox("View Settings", widget_APLs_AddEdit) ;
    checkBox_APLs_AddEdit_Settings_Edit = new QCheckBox("Edit Settings", widget_APLs_AddEdit) ;

    pushButton_APLs_AddEdit_Submit = new QPushButton("Submit", widget_APLs_AddEdit) ;

    layout_APLs_AddEdit_Title->addWidget(label_APLs_AddEdit_Name) ;
    layout_APLs_AddEdit_Title->addWidget(lineEdit_APLs_AddEdit_Name) ;

    layout_APLs_AddEdit_Active->addWidget(checkBox_APLs_AddEdit_Active) ;

    layout_APLs_AddEdit_TitleActive->addLayout(layout_APLs_AddEdit_Title) ;
    layout_APLs_AddEdit_TitleActive->addLayout(layout_APLs_AddEdit_Active) ;
    layout_APLs_AddEdit_TitleActive->addStretch() ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->setSpacing(2) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addSpacing(20) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(label_APLs_AddEdit_Research_Topics) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Research_Topics_View) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Research_Topics_Add) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Research_Topics_Edit) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Research_Topics_Delete) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addSpacing(20) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(label_APLs_AddEdit_Participants) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Participants_View) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Participants_Add) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Participants_Edit) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Participants_Delete) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addSpacing(20) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(label_APLs_AddEdit_Questionnaires) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Questionnaires_View) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Questionnaires_Add) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Questionnaires_Edit) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnA->addWidget(checkBox_APLs_AddEdit_Questionnaires_Delete) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnA->addStretch() ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->setSpacing(2) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addSpacing(20) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(label_APLs_AddEdit_Users) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Users_View) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Users_Add) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Users_Edit) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Users_Delete) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addSpacing(20) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(label_APLs_AddEdit_Other) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_SearchDatabase) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_BackUp) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Collaborate) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Export) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addSpacing(20) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(label_APLs_AddEdit_Settings) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Settings_View) ;
    layout_APLs_AddEdit_CheckBoxes_ColumnB->addWidget(checkBox_APLs_AddEdit_Settings_Edit) ;

    layout_APLs_AddEdit_CheckBoxes_ColumnB->addStretch() ;

    layout_APLs_AddEdit_CheckBoxes->addSpacing(20) ;
    layout_APLs_AddEdit_CheckBoxes->addLayout(layout_APLs_AddEdit_CheckBoxes_ColumnA) ;
    layout_APLs_AddEdit_CheckBoxes->addSpacing(20) ;
    layout_APLs_AddEdit_CheckBoxes->addLayout(layout_APLs_AddEdit_CheckBoxes_ColumnB) ;
    layout_APLs_AddEdit_CheckBoxes->addStretch() ;

    layout_APLs_AddEdit_Button->addWidget(pushButton_APLs_AddEdit_Submit) ;

    layout_APLs_AddEdit->addLayout(layout_APLs_AddEdit_TitleActive) ;
    layout_APLs_AddEdit->addLayout(layout_APLs_AddEdit_CheckBoxes) ;
    layout_APLs_AddEdit->addLayout(layout_APLs_AddEdit_Button) ;

    widget_APLs_AddEdit->setLayout(layout_APLs_AddEdit) ;

    /*
     * Widget - Participants View
     */
    widget_Participants_View = new QWidget() ;
    layout_Vertical_Participants_View = new QVBoxLayout() ;
    layout_Horizontal_Participants_View = new QHBoxLayout() ;

    tableWidget_Participants_View = new QTableWidget(widget_Participants_View) ;
    tableWidget_Participants_View->setEditTriggers(QAbstractItemView::NoEditTriggers) ;

    pushButton_Participants_View_Add = new QPushButton("Add", widget_Participants_View) ;
    pushButton_Participants_View_Edit = new QPushButton("Edit", widget_Participants_View) ;
    pushButton_Participants_View_Delete = new QPushButton("Delete", widget_Participants_View) ;

    layout_Horizontal_Participants_View->addWidget(pushButton_Participants_View_Add) ;
    layout_Horizontal_Participants_View->addWidget(pushButton_Participants_View_Edit) ;
    layout_Horizontal_Participants_View->addWidget(pushButton_Participants_View_Delete) ;

    layout_Vertical_Participants_View->addWidget(tableWidget_Participants_View) ;
    layout_Vertical_Participants_View->addLayout(layout_Horizontal_Participants_View) ;

    widget_Participants_View->setLayout(layout_Vertical_Participants_View) ;

    /*
     * Widget - Participants Add/Edit
     */
    widget_Participants_AddEdit = new QWidget() ;
    layout_Participants_AddEdit = new QVBoxLayout() ;
    layout_Vertical_Participants_AddEdit = new QVBoxLayout() ;
    layout_Horizontal_Participants_AddEdit = new QHBoxLayout() ;
    layout_Horizontal_Participants_AddEdit_Buttons = new QHBoxLayout() ;
    layout_Form_Participants_AddEdit_Form = new QFormLayout() ;

    label_Participants_AddEdit_Participant_Title = new QLabel("<b>Participant:</b>", widget_Participants_AddEdit) ;

    label_Participants_AddEdit_ParticipantID = new QLabel("Participant ID", widget_Participants_AddEdit) ;
    label_Participants_AddEdit_ParticipantID_GeneratedID = new QLabel("Please Wait...", widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Participant_Forename = new QLabel("Forename:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Participant_Forename = new QLineEdit(widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Participant_Surname = new QLabel("Surname:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Participant_Surname = new QLineEdit(widget_Participants_AddEdit) ;

    label_Participants_AddEdit_DateOfBirth = new QLabel("Date of Birth:", widget_Participants_AddEdit) ;
    dateEdit_Participants_AddEdit_DateOfBirth = new QDateEdit(widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Sex = new QLabel("Sex:", widget_Participants_AddEdit) ;
    radioButton_Participants_AddEdit_Male = new QRadioButton("Male", widget_Participants_AddEdit) ;
    radioButton_Participants_AddEdit_Female = new QRadioButton("Female", widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Guardian_Title = new QLabel("<b>Guardian:</b>", widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Guardian_Forename = new QLabel("Forename:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Guardian_Forename = new QLineEdit(widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Guardian_Surname = new QLabel("Surname:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Guardian_Surname = new QLineEdit(widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Contact_Title = new QLabel("<b>Contact Info:</b>", widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Contact_Home = new QLabel("Home:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Contact_Home = new QLineEdit(widget_Participants_AddEdit) ;
    label_Participants_AddEdit_Contact_Work = new QLabel("Work:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Contact_Work = new QLineEdit(widget_Participants_AddEdit) ;
    label_Participants_AddEdit_Contact_Mobile = new QLabel("Mobile:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Contact_Mobile = new QLineEdit(widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Address_Title = new QLabel("<b>Address:</b>", widget_Participants_AddEdit) ;

    label_Participants_AddEdit_Address_Line1 = new QLabel("House Name:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Address_Line1 = new QLineEdit(widget_Participants_AddEdit) ;
    label_Participants_AddEdit_Address_Line2 = new QLabel("Street:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Address_Line2 = new QLineEdit(widget_Participants_AddEdit) ;
    label_Participants_AddEdit_Address_Line3 = new QLabel("Town:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Address_Line3 = new QLineEdit(widget_Participants_AddEdit) ;
    label_Participants_AddEdit_Address_Line4 = new QLabel("County:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Address_Line4 = new QLineEdit(widget_Participants_AddEdit) ;
    label_Participants_AddEdit_Address_PostCode = new QLabel("Post Code:", widget_Participants_AddEdit) ;
    lineEdit_Participants_AddEdit_Address_PostCode = new QLineEdit(widget_Participants_AddEdit) ;

    pushButton_Participants_AddEdit_Submit = new QPushButton("Submit", widget_Participants_AddEdit) ;

    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Participant_Title) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Participant_Forename, lineEdit_Participants_AddEdit_Participant_Forename) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Participant_Surname, lineEdit_Participants_AddEdit_Participant_Surname) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_ParticipantID, label_Participants_AddEdit_ParticipantID_GeneratedID) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_DateOfBirth, dateEdit_Participants_AddEdit_DateOfBirth) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Sex, radioButton_Participants_AddEdit_Male) ;
    layout_Form_Participants_AddEdit_Form->addRow("", radioButton_Participants_AddEdit_Female) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Guardian_Title) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Guardian_Forename, lineEdit_Participants_AddEdit_Guardian_Forename) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Guardian_Surname, lineEdit_Participants_AddEdit_Guardian_Surname) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Contact_Title) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Contact_Home, lineEdit_Participants_AddEdit_Contact_Home) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Contact_Work, lineEdit_Participants_AddEdit_Contact_Work) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Contact_Mobile, lineEdit_Participants_AddEdit_Contact_Mobile) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Address_Title) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Address_Line1, lineEdit_Participants_AddEdit_Address_Line1) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Address_Line2, lineEdit_Participants_AddEdit_Address_Line2) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Address_Line3, lineEdit_Participants_AddEdit_Address_Line3) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Address_Line4, lineEdit_Participants_AddEdit_Address_Line4) ;
    layout_Form_Participants_AddEdit_Form->addRow(label_Participants_AddEdit_Address_PostCode, lineEdit_Participants_AddEdit_Address_PostCode) ;

    layout_Horizontal_Participants_AddEdit_Buttons->addWidget(pushButton_Participants_AddEdit_Submit) ;

    layout_Horizontal_Participants_AddEdit->addLayout(layout_Form_Participants_AddEdit_Form) ;

    layout_Vertical_Participants_AddEdit->addLayout(layout_Horizontal_Participants_AddEdit) ;
    layout_Vertical_Participants_AddEdit->addLayout(layout_Horizontal_Participants_AddEdit_Buttons) ;

    widget_Participants_AddEdit->setLayout(layout_Vertical_Participants_AddEdit) ;

    /*
     * Widget - Questionnaires View
     */
    widget_Questionnaires_View = new QWidget() ;

    layout_Vertical_Questionnaires_View = new QVBoxLayout() ;
    layout_Horizontal_Questionnaires_View = new QHBoxLayout() ;

    tableWidget_Questionnaires_View = new QTableWidget(widget_Questionnaires_View) ;
    tableWidget_Questionnaires_View->setEditTriggers(QAbstractItemView::NoEditTriggers) ;

    pushButton_Questionnaires_View_Add = new QPushButton("Add", widget_Questionnaires_View) ;
    pushButton_Questionnaires_View_Edit = new QPushButton("Edit", widget_Questionnaires_View) ;
    pushButton_Questionnaires_View_Delete = new QPushButton("Delete", widget_Questionnaires_View) ;

    layout_Horizontal_Questionnaires_View->addWidget(pushButton_Questionnaires_View_Add) ;
    layout_Horizontal_Questionnaires_View->addWidget(pushButton_Questionnaires_View_Edit) ;
    layout_Horizontal_Questionnaires_View->addWidget(pushButton_Questionnaires_View_Delete) ;

    layout_Vertical_Questionnaires_View->addWidget(tableWidget_Questionnaires_View) ;
    layout_Vertical_Questionnaires_View->addLayout(layout_Horizontal_Questionnaires_View) ;

    widget_Questionnaires_View->setLayout(layout_Vertical_Questionnaires_View) ;

    /*
     * Widget - Questionnaires Add/Edit
     */
    widget_Questionnaires_AddEdit = new QWidget() ;

    layout_Vertical_Questionnaires_AddEdit = new QVBoxLayout() ;

    layout_Horizontal_Questionnaires_AddEdit_Title = new QHBoxLayout() ;
    layout_Horizontal_Questionnaires_AddEdit_Note = new QHBoxLayout() ;
    layout_Vertical_Questionnaires_AddEdit_Questions = new QVBoxLayout() ;
    layout_Vertical_Questionnaires_AddEdit_New_Question = new QVBoxLayout() ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Title = new QHBoxLayout() ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Range = new QHBoxLayout() ;
    layout_Horizontal_Questionnaires_AddEdit_AddLine = new QHBoxLayout() ;

    signalMapperQuestionnaireAddEdit = new QSignalMapper(this) ;

    label_Questionnaires_AddEdit_Title = new QLabel("Questionnaire ID:", widget_Questionnaires_AddEdit) ;
    label_Questionnaires_AddEdit_Title_ID = new QLabel("Please Wait...", widget_Questionnaires_AddEdit) ;

    layout_Horizontal_Questionnaires_AddEdit_Title->addWidget(label_Questionnaires_AddEdit_Title) ;
    layout_Horizontal_Questionnaires_AddEdit_Title->addWidget(label_Questionnaires_AddEdit_Title_ID) ;
    layout_Horizontal_Questionnaires_AddEdit_Title->addStretch() ;

    label_Questionnaires_AddEdit_Note_Title = new QLabel("Note:", widget_Questionnaires_AddEdit) ;
    lineEdit_Questionnaires_AddEdit_Note = new QLineEdit(widget_Questionnaires_AddEdit) ;

    layout_Horizontal_Questionnaires_AddEdit_Note->addWidget(label_Questionnaires_AddEdit_Note_Title) ;
    layout_Horizontal_Questionnaires_AddEdit_Note->addWidget(lineEdit_Questionnaires_AddEdit_Note) ;

    layout_Vertical_Questionnaires_AddEdit_Questions->setSpacing(0) ;

    label_Questionnaires_AddEdit_Question = new QLabel("Question:", widget_Questionnaires_AddEdit) ;
    lineEdit_Questionnaires_AddEdit_Question = new QLineEdit(widget_Questionnaires_AddEdit) ;

    layout_Horizontal_Questionnaires_AddEdit_New_Question_Title->addWidget(label_Questionnaires_AddEdit_Question) ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Title->addWidget(lineEdit_Questionnaires_AddEdit_Question) ;

    comboBox_Questionnaires_AddEdit_New_Question_Question_Type = new QComboBox(widget_Questionnaires_AddEdit) ;
    comboBox_Questionnaires_AddEdit_New_Question_Question_Type->addItem("Boolean") ;
    comboBox_Questionnaires_AddEdit_New_Question_Question_Type->addItem("Text") ;
    comboBox_Questionnaires_AddEdit_New_Question_Question_Type->addItem("Number") ;

    label_Questionnaires_AddEdit_Question_Range_Base = new QLabel("Base:", widget_Questionnaires_AddEdit) ;
    lineEdit_Questionnaires_AddEdit_Question_Range_Base = new QLineEdit(widget_Questionnaires_AddEdit) ;
    label_Questionnaires_AddEdit_Question_Range_Range = new QLabel("Range:", widget_Questionnaires_AddEdit) ;
    lineEdit_Questionnaires_AddEdit_Question_Range_Range = new QLineEdit(widget_Questionnaires_AddEdit) ;

    lineEdit_Questionnaires_AddEdit_Question_Range_Base->setEnabled(false) ;
    lineEdit_Questionnaires_AddEdit_Question_Range_Base->setInputMask("9999") ;
    lineEdit_Questionnaires_AddEdit_Question_Range_Base->setMaxLength(4) ;

    lineEdit_Questionnaires_AddEdit_Question_Range_Range->setEnabled(false) ;
    lineEdit_Questionnaires_AddEdit_Question_Range_Range->setInputMask("9999") ;
    lineEdit_Questionnaires_AddEdit_Question_Range_Range->setMaxLength(4) ;

    layout_Horizontal_Questionnaires_AddEdit_New_Question_Range->addWidget(label_Questionnaires_AddEdit_Question_Range_Base) ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Range->addWidget(lineEdit_Questionnaires_AddEdit_Question_Range_Base) ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Range->addWidget(label_Questionnaires_AddEdit_Question_Range_Range) ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Range->addWidget(lineEdit_Questionnaires_AddEdit_Question_Range_Range) ;
    layout_Horizontal_Questionnaires_AddEdit_New_Question_Range->addStretch() ;

    layout_Vertical_Questionnaires_AddEdit_New_Question->addLayout(layout_Horizontal_Questionnaires_AddEdit_New_Question_Title) ;
    layout_Vertical_Questionnaires_AddEdit_New_Question->addWidget(comboBox_Questionnaires_AddEdit_New_Question_Question_Type) ;
    layout_Vertical_Questionnaires_AddEdit_New_Question->addLayout(layout_Horizontal_Questionnaires_AddEdit_New_Question_Range) ;

    pushButton_Questionnaires_AddEdit_AddLine = new QPushButton("Add Question", widget_Questionnaires_AddEdit) ;

    layout_Horizontal_Questionnaires_AddEdit_AddLine->addStretch() ;
    layout_Horizontal_Questionnaires_AddEdit_AddLine->addWidget(pushButton_Questionnaires_AddEdit_AddLine) ;

    pushButton_Questionnaires_AddEdit_Submit = new QPushButton("Submit", widget_Questionnaires_AddEdit) ;

    layout_Vertical_Questionnaires_AddEdit->addLayout(layout_Horizontal_Questionnaires_AddEdit_Title) ;
    layout_Vertical_Questionnaires_AddEdit->addLayout(layout_Horizontal_Questionnaires_AddEdit_Note) ;
    layout_Vertical_Questionnaires_AddEdit->addLayout(layout_Vertical_Questionnaires_AddEdit_Questions) ;
    layout_Vertical_Questionnaires_AddEdit->addStretch() ;
    layout_Vertical_Questionnaires_AddEdit->addLayout(layout_Vertical_Questionnaires_AddEdit_New_Question) ;
    layout_Vertical_Questionnaires_AddEdit->addLayout(layout_Horizontal_Questionnaires_AddEdit_AddLine) ;
    layout_Vertical_Questionnaires_AddEdit->addWidget(pushButton_Questionnaires_AddEdit_Submit) ;

    widget_Questionnaires_AddEdit->setLayout(layout_Vertical_Questionnaires_AddEdit) ;

    /*
     * Stacked Widget
     */
    stackedWidget_MainWorkingArea = new QStackedWidget(frame_MainWorkingArea) ;
    stackedWidget_MainWorkingArea->setGeometry(0, 0,
                                               frame_MainWorkingArea->geometry().width(),
                                               frame_MainWorkingArea->geometry().height()) ;
    stackedWidget_MainWorkingArea->show();

    //Set Widgets' Parent
    widget_Home->setParent(stackedWidget_MainWorkingArea) ;
    widget_Users_View->setParent(stackedWidget_MainWorkingArea) ;
    widget_Users_AddEdit->setParent(stackedWidget_MainWorkingArea) ;
    widget_APLs_View->setParent(stackedWidget_MainWorkingArea) ;
    widget_APLs_AddEdit->setParent(stackedWidget_MainWorkingArea) ;
    widget_Participants_View->setParent(stackedWidget_MainWorkingArea) ;
    widget_Participants_AddEdit->setParent(stackedWidget_MainWorkingArea) ;
    widget_Questionnaires_View->setParent(stackedWidget_MainWorkingArea) ;
    widget_Questionnaires_AddEdit->setParent(stackedWidget_MainWorkingArea) ;

    //Hide All Widgets
    widget_Home->hide() ;
    widget_Users_View->hide() ;
    widget_Users_AddEdit->hide() ;
    widget_APLs_View->hide() ;
    widget_APLs_AddEdit->hide() ;
    widget_Participants_View->hide() ;
    widget_Participants_AddEdit->hide() ;
    widget_Questionnaires_View->hide() ;
    widget_Questionnaires_AddEdit->hide() ;
}

void ViewMainScreen::initButtons_TertiaryButtons()
{
    /*
     * Settings
     */
    //APL
    pushButton_Menu_Tertiary_Button_APL_View = new QPushButton("View\nAPLs", this) ;
    pushButton_Menu_Tertiary_Button_APL_Add = new QPushButton("Add\nAPL", this) ;
    pushButton_Menu_Tertiary_Button_APL_Edit = new QPushButton("Edit\nAPL", this) ;
    pushButton_Menu_Tertiary_Button_APL_Remove = new QPushButton("Remove\nAPL(s)", this) ;

    pushButton_Menu_Tertiary_Buttons_Settings_APLs.push_back(pushButton_Menu_Tertiary_Button_APL_View) ;
    pushButton_Menu_Tertiary_Buttons_Settings_APLs.push_back(pushButton_Menu_Tertiary_Button_APL_Add) ;
    pushButton_Menu_Tertiary_Buttons_Settings_APLs.push_back(pushButton_Menu_Tertiary_Button_APL_Edit) ;
    pushButton_Menu_Tertiary_Buttons_Settings_APLs.push_back(pushButton_Menu_Tertiary_Button_APL_Remove) ;

    //User
    pushButton_Menu_Tertiary_Button_User_View = new QPushButton("View\nUsers", this) ;
    pushButton_Menu_Tertiary_Button_User_Add = new QPushButton("Add\nUser", this) ;
    pushButton_Menu_Tertiary_Button_User_Edit = new QPushButton("Edit\nUser", this) ;
    pushButton_Menu_Tertiary_Button_User_Remove = new QPushButton("Remove\nUser(s)", this) ;

    pushButton_Menu_Tertiary_Buttons_Settings_Users.push_back(pushButton_Menu_Tertiary_Button_User_View) ;
    pushButton_Menu_Tertiary_Buttons_Settings_Users.push_back(pushButton_Menu_Tertiary_Button_User_Add) ;
    pushButton_Menu_Tertiary_Buttons_Settings_Users.push_back(pushButton_Menu_Tertiary_Button_User_Edit) ;
    pushButton_Menu_Tertiary_Buttons_Settings_Users.push_back(pushButton_Menu_Tertiary_Button_User_Remove) ;

    QString STYLESHEET = getTertiaryButtonStyleSheet() ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Settings_APLs.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Settings_APLs.at(i)->setGeometry((MAIN_MENU_PADDING+PRIMARY_BUTTON_WIDTH-PRIMARY_BUTTON_GRADIENT+SECONDARY_BUTTON_WIDTH-SECONDARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)), SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Tertiary_Buttons_Settings_APLs.at(i)->setStyleSheet(STYLESHEET) ;
    }

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Settings_Users.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Settings_Users.at(i)->setGeometry((MAIN_MENU_PADDING+PRIMARY_BUTTON_WIDTH-PRIMARY_BUTTON_GRADIENT+SECONDARY_BUTTON_WIDTH-SECONDARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)), SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Tertiary_Buttons_Settings_Users.at(i)->setStyleSheet(STYLESHEET) ;
    }

    /*
     * Participants
     */
    pushButton_Menu_Tertiary_Button_Participants_View = new QPushButton("View\nParticipants", this) ;
    pushButton_Menu_Tertiary_Button_Participants_Add = new QPushButton("Add\nParticipants", this) ;
    pushButton_Menu_Tertiary_Button_Participants_Edit = new QPushButton("Edit\nParticipants", this) ;
    pushButton_Menu_Tertiary_Button_Participants_Remove = new QPushButton("Remove\nParticipants", this) ;

    pushButton_Menu_Tertiary_Buttons_Participants.push_back(pushButton_Menu_Tertiary_Button_Participants_View) ;
    pushButton_Menu_Tertiary_Buttons_Participants.push_back(pushButton_Menu_Tertiary_Button_Participants_Add) ;
    pushButton_Menu_Tertiary_Buttons_Participants.push_back(pushButton_Menu_Tertiary_Button_Participants_Edit) ;
    pushButton_Menu_Tertiary_Buttons_Participants.push_back(pushButton_Menu_Tertiary_Button_Participants_Remove) ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Participants.at(i)->setGeometry((MAIN_MENU_PADDING+PRIMARY_BUTTON_WIDTH-PRIMARY_BUTTON_GRADIENT+SECONDARY_BUTTON_WIDTH-SECONDARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)), SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Tertiary_Buttons_Participants.at(i)->setStyleSheet(STYLESHEET) ;
    }

    /*
     * Questionnaires & Questions (View only)
     */
    //Questionnaires
    pushButton_Menu_Tertiary_Button_Questionnaire_View = new QPushButton("View\nQuestionnaires", this) ;
    pushButton_Menu_Tertiary_Button_Questionnaire_Add  = new QPushButton("Add\nQuestionnaire", this) ;
    pushButton_Menu_Tertiary_Button_Questionnaire_Edit  = new QPushButton("Edit\nQuestionnaire", this) ;
    pushButton_Menu_Tertiary_Button_Questionnaire_Remove  = new QPushButton("Remove\nQuestionnaires", this) ;

    pushButton_Menu_Tertiary_Buttons_Questionnaires.push_back(pushButton_Menu_Tertiary_Button_Questionnaire_View) ;
    pushButton_Menu_Tertiary_Buttons_Questionnaires.push_back(pushButton_Menu_Tertiary_Button_Questionnaire_Add) ;
    pushButton_Menu_Tertiary_Buttons_Questionnaires.push_back(pushButton_Menu_Tertiary_Button_Questionnaire_Edit) ;
    pushButton_Menu_Tertiary_Buttons_Questionnaires.push_back(pushButton_Menu_Tertiary_Button_Questionnaire_Remove) ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Questionnaires.at(i)->setGeometry((MAIN_MENU_PADDING+PRIMARY_BUTTON_WIDTH-PRIMARY_BUTTON_GRADIENT+SECONDARY_BUTTON_WIDTH-SECONDARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)), SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Tertiary_Buttons_Questionnaires.at(i)->setStyleSheet(STYLESHEET) ;
    }

    //Questions
    pushButton_Menu_Tertiary_Button_Questions_View = new QPushButton("View\nQuestions", this) ;

    pushButton_Menu_Tertiary_Buttons_Questions.push_back(pushButton_Menu_Tertiary_Button_Questions_View) ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Questions.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Questions.at(i)->setGeometry((MAIN_MENU_PADDING+PRIMARY_BUTTON_WIDTH-PRIMARY_BUTTON_GRADIENT+SECONDARY_BUTTON_WIDTH-SECONDARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)), SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Tertiary_Buttons_Questions.at(i)->setStyleSheet(STYLESHEET) ;
    }
}

void ViewMainScreen::initButtons_SecondaryButtons()
{
    /*
     * Settings
     */
    pushButton_Menu_Secondary_Buttons_Settings_APLs = new QPushButton("APLs", this) ;
    pushButton_Menu_Secondary_Buttons_Settings_Users = new QPushButton("Users", this) ;

    pushButton_Menu_Secondary_Buttons_Settings.push_back(pushButton_Menu_Secondary_Buttons_Settings_APLs) ;
    pushButton_Menu_Secondary_Buttons_Settings.push_back(pushButton_Menu_Secondary_Buttons_Settings_Users) ;

    QString STYLESHEET = getSecondaryButtonStyleSheet() ;

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Settings.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Settings.at(i)->setGeometry((MAIN_MENU_PADDING+(PRIMARY_BUTTON_WIDTH)-PRIMARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)),
                                                        SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Secondary_Buttons_Settings.at(i)->setStyleSheet(STYLESHEET) ;
    }

    /*
     * Participants
     */
    pushButton_Menu_Secondary_Button_Participants = new QPushButton("Participants", this) ;

    pushButton_Menu_Secondary_Buttons_Participants.push_back(pushButton_Menu_Secondary_Button_Participants) ;

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Participants.at(i)->setGeometry((MAIN_MENU_PADDING+(PRIMARY_BUTTON_WIDTH)-PRIMARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)),
                                                        SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Secondary_Buttons_Participants.at(i)->setStyleSheet(STYLESHEET) ;
    }

    /*
     * Questionnaires
     */
    pushButton_Menu_Secondary_Button_Questionnaires = new QPushButton("Questionnaires", this) ;
    pushButton_Menu_Secondary_Button_Questions = new QPushButton("Questions", this) ;

    pushButton_Menu_Secondary_Buttons_Questionnaires.push_back(pushButton_Menu_Secondary_Button_Questionnaires) ;
    pushButton_Menu_Secondary_Buttons_Questionnaires.push_back(pushButton_Menu_Secondary_Button_Questions) ;

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Questionnaires.at(i)->setGeometry((MAIN_MENU_PADDING+(PRIMARY_BUTTON_WIDTH)-PRIMARY_BUTTON_GRADIENT),
                                                        (MAIN_MENU_PADDING+(i*SECONDARY_BUTTON_HEIGHT)),
                                                        SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Secondary_Buttons_Questionnaires.at(i)->setStyleSheet(STYLESHEET) ;
    }
}

void ViewMainScreen::initButtons_PrimaryButtons()
{
    pushButton_Menu_Primary_Button_Home = new QPushButton("Home", this) ;
    pushButton_Menu_Primary_Button_Research = new QPushButton("Research", this) ;
    pushButton_Menu_Primary_Button_Questionnaires = new QPushButton("Questionnaires", this) ;
    pushButton_Menu_Primary_Button_Participants = new QPushButton("Participants", this) ;
    pushButton_Menu_Primary_Button_Settings = new QPushButton("Settings", this) ;
    pushButton_Menu_Primary_Button_Collaborate_BackUp = new QPushButton("Collaborate\nBack-Up", this) ;
    pushButton_Menu_Primary_Button_Lock = new QPushButton("Lock", this) ;
    pushButton_Menu_Primary_Button_Logout = new QPushButton("Logout", this) ;

    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Home) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Research) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Questionnaires) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Participants) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Settings) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Collaborate_BackUp) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Lock) ;
    pushButton_Menu_Primary_Buttons.push_back(pushButton_Menu_Primary_Button_Logout) ;

    QString STYLESHEET = getPrimaryButtonStyleSheet() ;

    for (int i = 0; i < pushButton_Menu_Primary_Buttons.size(); i++)
    {
        pushButton_Menu_Primary_Buttons.at(i)->setGeometry(MAIN_MENU_PADDING,(MAIN_MENU_PADDING+(i*PRIMARY_BUTTON_HEIGHT)),
                                                   PRIMARY_BUTTON_WIDTH, PRIMARY_BUTTON_HEIGHT) ;
        pushButton_Menu_Primary_Buttons.at(i)->setStyleSheet(STYLESHEET) ;
    }
}

void ViewMainScreen::initFrame_LockScreen()
{
    QString STYLESHEET = getStyleSheetForLockFrame() ;

    frame_LockScreen = new QFrame(this) ;
    frame_LockScreen->setStyleSheet(STYLESHEET);
    frame_LockScreen->setGeometry(0,0,this->geometry().width(),this->geometry().height()) ;

    frame_LockScreen->hide() ;
}

void ViewMainScreen::showFrameLockScreen(bool show)
{
    if (show)
    {
        frame_LockScreen->show() ;
    }
    else
    {
        frame_LockScreen->hide() ;
    }
}

void ViewMainScreen::initFrame_LoginScreen()
{
    QString STYLESHEET = getStyleSheetForLoginScreen() ;

    frame_LoginScreen = new QFrame(this) ;
    frame_LoginScreen->setStyleSheet(STYLESHEET) ;

    frame_LoginScreen->setGeometry(((this->size().width()/2)-(LOGIN_FRAME_WIDTH/2)),
                             ((this->size().height()/2)-(LOGIN_FRAME_HEIGHT/2)),
                             LOGIN_FRAME_WIDTH, LOGIN_FRAME_HEIGHT) ;

    gridLayout_Login = new QGridLayout() ;
    gridLayout_Login->setVerticalSpacing(1) ;

    lineEdit_Login_Username = new QLineEdit() ;
    lineEdit_Login_Username->setPlaceholderText("username") ;

    lineEdit_Login_Password = new QLineEdit() ;
    lineEdit_Login_Password->setEchoMode(QLineEdit::Password) ;
    lineEdit_Login_Password->setPlaceholderText("password") ;

    pushButton_Login_Login = new QPushButton() ;
    pushButton_Login_Login->setText("Login") ;

    gridLayout_Login->addWidget(lineEdit_Login_Username, 0, 0, 1, 4) ;
    gridLayout_Login->addWidget(lineEdit_Login_Password, 1, 0, 1, 4) ;
    gridLayout_Login->addWidget(pushButton_Login_Login, 3, 1, 1, 2) ;

    frame_LoginScreen->setLayout(gridLayout_Login) ;

    frame_LoginScreen->hide() ;
}

void ViewMainScreen::showFrameLoginScreen(bool show)
{
    if (show)
    {
        frame_LoginScreen->show() ;
    }
    else
    {
        frame_LoginScreen->hide() ;
    }
}

/*
 * Show Widget
 */
void ViewMainScreen::showWidgetInMainWorkingStackedWidget(QWidget *widget)
{
    stackedWidget_MainWorkingArea->removeWidget(stackedWidget_MainWorkingArea->currentWidget()) ;
    stackedWidget_MainWorkingArea->addWidget(widget) ;
    widget->show() ;
}

/*
 * Login
 */
void ViewMainScreen::loginAttempt()
{
    if (userLoggedIn)
    {
        if (lineEdit_Login_Password->text().toStdString() == currentUser.getPassword())
        {
            showFrameLockScreen(false) ;
            showFrameLoginScreen(false) ;
        }
    }
    else
    {
        Login login(lineEdit_Login_Username->text(),
                    lineEdit_Login_Password->text()) ;

        //Prepare Data to be written to Socket
        connection.setOutboundHeader("login") ;
        connection.setOutboundMessage(login) ;

        readyWrite() ;
    }
}

void ViewMainScreen::loginSuccessful(User user)
{
    currentUser = user ;
    userLoggedIn = true ;

    showFrameLoginScreen(false) ;
    showFrameLockScreen(false) ;

    lineEdit_Login_Username->setEnabled(false) ;
}

void ViewMainScreen::loginFailed()
{

}

/*
 * STYLESHEETS
 */
QString ViewMainScreen::getPrimaryButtonStyleSheet()
{
    QString stylesheet ;
    stylesheet = "" ;

    stylesheet.append("QPushButton") ;
    stylesheet.append("{") ;
    stylesheet.append("color: white;") ;
    stylesheet.append("background-color:#00CCFF ;") ;
    stylesheet.append("border-top-right-radius:20px ; ") ;
    stylesheet.append("border-bottom-right-radius:20px ;") ;
    stylesheet.append("background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #00A3CC, stop:1 #005266);") ;
    stylesheet.append("border-style:solid ;") ;
    stylesheet.append("border-color:black ;") ;
    stylesheet.append("font-family:\"Verdana\", Sans-serif ;") ;
    stylesheet.append("font-size:12px ;") ;
    stylesheet.append("}" ) ;

    stylesheet.append("QPushButton:hover") ;
    stylesheet.append("{") ;
    stylesheet.append("color: white;") ;
    stylesheet.append("background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #00728F, stop:1 #005B72);") ;
    stylesheet.append("}") ;

    return stylesheet ;
}

QString ViewMainScreen::getSecondaryButtonStyleSheet()
{
    QString stylesheet ;
    stylesheet = "" ;

    stylesheet.append("QPushButton") ;
    stylesheet.append("{") ;
    stylesheet.append("color: white;") ;
    stylesheet.append("background-color:#00CCFF ;") ;
    stylesheet.append("border-top-right-radius:20px ; ") ;
    stylesheet.append("border-bottom-right-radius:20px ;") ;
    stylesheet.append("background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #83FF83, stop:1 #346634);") ;
    stylesheet.append("border-style:solid ;") ;
    stylesheet.append("border-color:black ;") ;
    stylesheet.append("font-family:\"Verdana\", Sans-serif ;") ;
    stylesheet.append("font-size:12px ;") ;
    stylesheet.append("}" ) ;

    stylesheet.append("QPushButton:hover") ;
    stylesheet.append("{") ;
    stylesheet.append("color: white;") ;
    stylesheet.append("background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #5CB25C, stop:1 #254725);") ;
    stylesheet.append("}") ;

    return stylesheet ;
}

QString ViewMainScreen::getTertiaryButtonStyleSheet()
{
    QString stylesheet ;
    stylesheet = "" ;

    stylesheet.append("QPushButton") ;
    stylesheet.append("{") ;
    stylesheet.append("color: white;") ;
    stylesheet.append("background-color:#00CCFF ;") ;
    stylesheet.append("border-top-right-radius:20px ; ") ;
    stylesheet.append("border-top-left-radius:20px ; ") ;
    stylesheet.append("border-bottom-right-radius:20px ;") ;
    stylesheet.append("border-bottom-left-radius:20px ;") ;
    stylesheet.append("background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #FF9900, stop:1 #804C00);") ;
    stylesheet.append("border-style:solid ;") ;
    stylesheet.append("border-color:black ;") ;
    stylesheet.append("font-family:\"Verdana\", Sans-serif ;") ;
    stylesheet.append("font-size:12px ;") ;
    stylesheet.append("}" ) ;

    stylesheet.append("QPushButton:hover") ;
    stylesheet.append("{") ;
    stylesheet.append("color: white;") ;
    stylesheet.append("background: qlineargradient( x100:1 y1:0, x2:1 y2:0, stop:0 #CC7A00, stop:1 #7A4900);") ;
    stylesheet.append("}") ;

    return stylesheet ;
}

QString ViewMainScreen::getStyleSheetForLockFrame()
{
    QString stylesheet ;
    stylesheet = "" ;

    stylesheet.append("QFrame") ;
    stylesheet.append("{") ;
    stylesheet.append("background-color: rgba(150, 150, 150, 0.85) ;") ;
    stylesheet.append("background-image :url(\"C:/Users/Brian/Dropbox/Y.ECSC799 Project/Application/UCLDataManagement_v002/images/logo-ucl-transparent.png\") ;") ;
    stylesheet.append("background-repeat:no-repeat ;") ;
    stylesheet.append("background-position:center ;") ;
    stylesheet.append("}") ;

    return stylesheet ;
}

QString ViewMainScreen::getStyleSheetForLoginScreen()
{
    QString stylesheet ;
    stylesheet = "" ;

    stylesheet.append("QFrame") ;
    stylesheet.append("{") ;
    stylesheet.append("background-color: rgba(255, 255, 255, 0.75) ;") ;
    stylesheet.append("border: 2px solid green ;") ;
    stylesheet.append("border-radius:") ;
    stylesheet.append(QString::number((LOGIN_FRAME_WIDTH/2))) ;
    stylesheet.append("px ;") ;
    stylesheet.append("padding: 2px ;") ;
    stylesheet.append("}") ;

    return stylesheet ;
}

/*
 * Signals * Slots
 */

void ViewMainScreen::pushButton_Login_Login_clicked()
{
   loginAttempt() ;
}

//Primary

void ViewMainScreen::pushButton_Menu_Primary_Button_Settings_clicked()
{
    hideSecondaryMenuButtons() ;
    hideTertiaryMenuButtons() ;

    showMenuSecondaryButtonsSettings() ;
}

//Secondary

void ViewMainScreen::pushButton_Menu_Secondary_Buttons_Settings_APLs_clicked()
{
    hideTertiaryMenuButtons() ;

    pushButton_Menu_Tertiary_Button_APL_View->show() ;
    pushButton_Menu_Tertiary_Button_APL_Add->show() ;
    pushButton_Menu_Tertiary_Button_APL_Edit->show() ;
    pushButton_Menu_Tertiary_Button_APL_Remove->show() ;
}

void ViewMainScreen::pushButton_Menu_Secondary_Buttons_Settings_Users_clicked()
{
    hideTertiaryMenuButtons() ;

    pushButton_Menu_Tertiary_Button_User_View->show() ;
    pushButton_Menu_Tertiary_Button_User_Add->show() ;
    pushButton_Menu_Tertiary_Button_User_Edit->show() ;
    pushButton_Menu_Tertiary_Button_User_Remove->show() ;
}

//Tertiary

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_APLs_View_clicked()
{
    viewAccessPermissionListTableWidget() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_APLs_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditAccessPermissionList() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_APLs_Edit_clicked()
{
    //Get Selected Row
    QItemSelectionModel *selectedModel = tableWidget_APLs_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Access Permission List(APL) may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditAccessPermissionList() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_APLs_Delete_clicked()
{
    QMessageBox::StandardButton deleteAPL ;
    deleteAPL = QMessageBox::warning(this,
                                     "Warning",
                                     "Are you sure you wish to delete selected Access Permission List(s)?",
                         QMessageBox::Yes | QMessageBox::No) ;

    if (deleteAPL == QMessageBox::Yes)
    {
        deleteAccessPermissionList();
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_Users_View_clicked()
{
    viewUserTableWidget() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_Users_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditUser() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_Users_Edit_clicked()
{
    QItemSelectionModel *selectedModel = tableWidget_Users_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 User may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditUser() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Buttons_Settings_Users_Delete_clicked()
{
    QMessageBox::StandardButton deleteUserMessageBoxButton ;
    deleteUserMessageBoxButton = QMessageBox::warning(this,
                                 "Warning",
                                 "Are you sure you wish to delete selected User(s)?",
                                  QMessageBox::Yes | QMessageBox::No) ;

    if (deleteUserMessageBoxButton == QMessageBox::Yes)
    {
        deleteUser() ;
    }
}

void ViewMainScreen::pushButton_Users_AddEdit_Submit_clicked()
{
    bool userCompletedEveryField = true ;

    if (lineEdit_Users_AddEdit_Forename->text().isEmpty())
    {
        userCompletedEveryField = false ;

        lineEdit_Users_AddEdit_Forename->setText("<font color='red'>* Forename:</font>") ;
    }

    if (lineEdit_Users_AddEdit_Surname->text().isEmpty())
    {
        userCompletedEveryField = false ;

        lineEdit_Users_AddEdit_Surname->setText("<font color='red'>* Surname:</font>") ;
    }

    if (lineEdit_Users_AddEdit_Department->text().isEmpty())
    {
        userCompletedEveryField = false ;

        lineEdit_Users_AddEdit_Department->setText("<font color='red'>* Department:</font>") ;
    }

    if (lineEdit_Users_AddEdit_Role->text().isEmpty())
    {
        userCompletedEveryField = false ;

        lineEdit_Users_AddEdit_Role->setText("<font color='red'>* Role:</font>") ;
    }

    if (userCompletedEveryField)
    {
        if (userIsEditingNotAddingObject)
        {
            connection.setOutboundHeader("editUser") ;
        }
        else
        {
           connection.setOutboundHeader("addUser") ;
        }

        User user ;

        user.setUserId(label_Users_AddEdit_UserID_Generated_ID->text().toStdString()) ;
        user.setPassword(label_Users_AddEdit_Password_Default_Password->text().toStdString()) ;
        user.setForename(lineEdit_Users_AddEdit_Forename->text().toStdString()) ;
        user.setSurname(lineEdit_Users_AddEdit_Surname->text().toStdString()) ;
        user.setDepartment(lineEdit_Users_AddEdit_Department->text().toStdString()) ;
        user.setRole(lineEdit_Users_AddEdit_Role->text().toStdString()) ;

        AccessPermissionList apl ;
        for (unsigned i = 0; i < accessPermissionLists.size(); i++)
        {
            apl = accessPermissionLists.at(i) ;

            if (QString::fromStdString(apl.getName()) == comboBox_Users_AddEdit_APL->currentText())
            {
                user.setAccessPermissionList(apl) ;
            }
        }

        user.setIsAccountActive(checkBox_Users_AddEdit_AccountActive->isChecked()) ;

        if (userIsEditingNotAddingObject)
        {
            QItemSelectionModel *selectedModel = tableWidget_Users_View->selectionModel() ;
            QModelIndexList indexOfRows = selectedModel->selectedRows() ;

            User userForPw = users.at(indexOfRows.at(0).row()) ;
            user.setPassword(userForPw.getPassword()) ;
        }

        connection.setOutboundMessage(user) ;

        readyWrite() ;
    }
    else
    {
        QMessageBox::warning(this,
                             "Warning",
                             "All fields must be filled.",
                             QMessageBox::Ok) ;
    }
}

void ViewMainScreen::pushButton_Users_View_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditUser() ;
}

void ViewMainScreen::pushButton_Users_View_Edit_clicked()
{
    //Get Selected Row
    QItemSelectionModel *selectedModel = tableWidget_Users_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Access Permission List(APL) may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditUser() ;
    }
}

void ViewMainScreen::pushButton_Users_View_Delete_clicked()
{
    QMessageBox::StandardButton deleteUserMessageBoxButton ;
    deleteUserMessageBoxButton = QMessageBox::warning(this,
                                 "Warning",
                                 "Are you sure you wish to delete selected User(s)?",
                                  QMessageBox::Yes | QMessageBox::No) ;

    if (deleteUserMessageBoxButton == QMessageBox::Yes)
    {
        deleteUser() ;
    }
}

void ViewMainScreen::pushButton_APLs_View_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditAccessPermissionList() ;
}

void ViewMainScreen::pushButton_APLs_View_Edit_clicked()
{
    //Get Selected Row
    QItemSelectionModel *selectedModel = tableWidget_APLs_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Access Permission List(APL) may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditAccessPermissionList() ;
    }
}

void ViewMainScreen::pushButton_APLs_View_Delete_clicked()
{
    QMessageBox::StandardButton deleteAPLMessageBoxButton ;
    deleteAPLMessageBoxButton = QMessageBox::warning(this,
                                 "Warning",
                                 "Are you sure you wish to delete selected Access Permission List(s)?",
                                  QMessageBox::Yes | QMessageBox::No) ;

    if (deleteAPLMessageBoxButton == QMessageBox::Yes)
    {
        deleteAccessPermissionList(); ;
    }
}

void ViewMainScreen::pushButton_APLs_AddEdit_Submit_clicked()
{
    if (!lineEdit_APLs_AddEdit_Name->text().isEmpty())
    {
        if (userIsEditingNotAddingObject)
        {
            connection.setOutboundHeader("editAPL") ;
        }
        else
        {
            connection.setOutboundHeader("addAPL") ;
        }

        AccessPermissionList apl ;

        apl.setName(lineEdit_APLs_AddEdit_Name->text().toStdString()) ;

        //Is Active
        apl.setIsAccountActive(checkBox_APLs_AddEdit_Active->isChecked()) ;

        //Research Topics
        apl.setCanViewResearchTopics(checkBox_APLs_AddEdit_Research_Topics_View->isChecked()) ;
        apl.setCanAddResearchTopics(checkBox_APLs_AddEdit_Research_Topics_Add->isChecked()) ;
        apl.setCanRemoveResearchTopics(checkBox_APLs_AddEdit_Research_Topics_Delete->isChecked()) ;
        apl.setCanEditResearchTopics(checkBox_APLs_AddEdit_Research_Topics_Edit->isChecked()) ;

        //Participants
        apl.setCanViewParticipants(checkBox_APLs_AddEdit_Participants_View->isChecked()) ;
        apl.setCanAddParticipants(checkBox_APLs_AddEdit_Participants_Add->isChecked()) ;
        apl.setCanRemoveParticipants(checkBox_APLs_AddEdit_Participants_Delete->isChecked()) ;
        apl.setCanEditParticipants(checkBox_APLs_AddEdit_Participants_Edit->isChecked()) ;

        //Questionnaires
        apl.setCanViewQuestionnaires(checkBox_APLs_AddEdit_Questionnaires_View->isChecked()) ;
        apl.setCanAddQuestionnaires(checkBox_APLs_AddEdit_Questionnaires_Add->isChecked()) ;
        apl.setCanRemoveQuestionnaires(checkBox_APLs_AddEdit_Questionnaires_Delete->isChecked()) ;
        apl.setCanEditQuestionnaires(checkBox_APLs_AddEdit_Questionnaires_Edit->isChecked()) ;

        //Users
        apl.setCanViewUsers(checkBox_APLs_AddEdit_Users_View->isChecked()) ;
        apl.setCanAddUsers(checkBox_APLs_AddEdit_Users_Add->isChecked()) ;
        apl.setCanRemoveUsers(checkBox_APLs_AddEdit_Users_Delete->isChecked()) ;
        apl.setCanEditUsers(checkBox_APLs_AddEdit_Users_Edit->isChecked()) ;

        //Settings
        apl.setCanViewSettings(checkBox_APLs_AddEdit_Settings_View->isChecked()) ;
        apl.setCanEditSettings(checkBox_APLs_AddEdit_Settings_Edit->isChecked()) ;

        //Other
        apl.setCanSearchDatabase(checkBox_APLs_AddEdit_SearchDatabase->isChecked()) ;
        apl.setCanBackUp(checkBox_APLs_AddEdit_BackUp->isChecked()) ;
        apl.setCanCollaborate(checkBox_APLs_AddEdit_Collaborate->isChecked()) ;
        apl.setCanExport(checkBox_APLs_AddEdit_Export->isChecked()) ;

        connection.setOutboundMessage(apl) ;

        readyWrite() ;
    }
    else
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Access Permission List(APL) has no name.",
                             QMessageBox::Ok) ;
    }
}

void ViewMainScreen::tableWidget_Users_View_Cell_clicked(const QModelIndex &index)
{
    tableWidget_Users_View->selectRow(index.row()) ;
}

void ViewMainScreen::tableWidget_ALPs_View_Cell_clicked(const QModelIndex &index)
{
    tableWidget_APLs_View->selectRow(index.row()) ;
}

/*
 * Window Resize Capture
 */
void ViewMainScreen::resizeEvent ( QResizeEvent */*event*/ )
{
    frame_LockScreen->setGeometry(0,0,this->geometry().width(),this->geometry().height()) ;
    frame_LoginScreen->setGeometry(((this->size().width()/2)-(LOGIN_FRAME_WIDTH/2)),
                                 ((this->size().height()/2)-(LOGIN_FRAME_HEIGHT/2)),
                                 LOGIN_FRAME_WIDTH, LOGIN_FRAME_HEIGHT) ;

    frame_MainWorkingAreaBorder->setGeometry((MAIN_MENU_PADDING + PRIMARY_BUTTON_WIDTH + SECONDARY_BUTTON_WIDTH - PRIMARY_BUTTON_GRADIENT + SECONDARY_BUTTON_WIDTH - SECONDARY_BUTTON_GRADIENT + (MAIN_MENU_PADDING*4)),
                                       (MAIN_MENU_PADDING + TITLE_HEIGHT + (MAIN_MENU_PADDING*4)),
                                       (this->geometry().width() - MAIN_MENU_PADDING - PRIMARY_BUTTON_WIDTH + PRIMARY_BUTTON_GRADIENT - SECONDARY_BUTTON_WIDTH + SECONDARY_BUTTON_GRADIENT - SECONDARY_BUTTON_WIDTH + SECONDARY_BUTTON_GRADIENT - ((MAIN_MENU_PADDING*4)*3)),
                                       (this->geometry().height() - MAIN_MENU_PADDING - TITLE_HEIGHT - ((MAIN_MENU_PADDING*4)*2))) ;

    frame_MainWorkingArea->setGeometry((MAIN_MENU_PADDING*4),(MAIN_MENU_PADDING*4),
                                       (frame_MainWorkingAreaBorder->width()-((MAIN_MENU_PADDING*4)*2)),
                                       (frame_MainWorkingAreaBorder->height()-((MAIN_MENU_PADDING*4)*2))) ;

    stackedWidget_MainWorkingArea->setGeometry(0, 0,
                                               frame_MainWorkingArea->geometry().width(),
                                               frame_MainWorkingArea->geometry().height()) ;
}

void ViewMainScreen::getAllAccessPermissionLists()
{
    connection.setOutboundHeader("get*APLs") ;
    readyWrite() ;
}

void ViewMainScreen::updateAPLTableWidget()
{
    const int COLUMN_COUNT = 24 ;
    tableWidget_APLs_View->setColumnCount(COLUMN_COUNT) ;
    tableWidget_APLs_View->setRowCount(accessPermissionLists.size()) ;

    QStringList tableHeaders ;
    tableHeaders << "APL Name"
                 << "canViewResearchTopics" << "canAddResearchTopics" << "canRemoveResearchTopics" << "canEditResearchTopics"
                 << "canViewParticipants" << "canAddParticipants" << "canRemoveParticipants" << "canEditParticipants"
                 << "canViewQuestionnaires" << "canAddQuestionnaires" << "canRemoveQuestionnaires" << "canEditQuestionnaires"
                 << "canViewUsers" << "canEditUsers" << "canRemoveUsers" << "canEditUsers"
                 << "canViewSettings" << "canEditSettings"
                 << "canSearchDatabase" << "canBackUp" << "canCollaborate" << "canExport"
                 << "isAccountActive" ;

    tableWidget_APLs_View->setHorizontalHeaderLabels(tableHeaders) ;

    AccessPermissionList apl ;
    apl = accessPermissionLists.at(0) ;

    std::string aplSerializedString ;
    aplSerializedString = " " ;

    for (unsigned row = 0; row < accessPermissionLists.size(); row++)
    {
        apl = accessPermissionLists.at(row) ;

        tableWidget_APLs_View->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(
                                                                        apl.getName()))) ;

        aplSerializedString = apl.simpleSerialize() ;

        for (int column = 1; column < COLUMN_COUNT; column++)
        {
            if (aplSerializedString.at(column) == '1')
            {
                tableWidget_APLs_View->setItem(row, column, new QTableWidgetItem("Y")) ;
            }
            else
            {
                tableWidget_APLs_View->setItem(row, column, new QTableWidgetItem("N")) ;
            }
        }
    }
}

void ViewMainScreen::viewAccessPermissionListTableWidget()
{
    getAllAccessPermissionLists() ;
}

void ViewMainScreen::viewAddEditAccessPermissionList()
{
    if (!userIsEditingNotAddingObject)
    {
        pushButton_APLs_AddEdit_Submit->setText("Add") ;
        lineEdit_APLs_AddEdit_Name->setEnabled(true) ;
        lineEdit_APLs_AddEdit_Name->setText("") ;

        //Is Active
        checkBox_APLs_AddEdit_Active->setChecked(true) ;

        //Research Topics
        checkBox_APLs_AddEdit_Research_Topics_View->setChecked(false) ;
        checkBox_APLs_AddEdit_Research_Topics_Add->setChecked(false) ;
        checkBox_APLs_AddEdit_Research_Topics_Delete->setChecked(false) ;
        checkBox_APLs_AddEdit_Research_Topics_Edit->setChecked(false) ;

        //Participants
        checkBox_APLs_AddEdit_Participants_View->setChecked(false) ;
        checkBox_APLs_AddEdit_Participants_Add->setChecked(false) ;
        checkBox_APLs_AddEdit_Participants_Delete->setChecked(false) ;
        checkBox_APLs_AddEdit_Participants_Edit->setChecked(false) ;

        //Questionnaires
        checkBox_APLs_AddEdit_Questionnaires_View->setChecked(false) ;
        checkBox_APLs_AddEdit_Questionnaires_Add->setChecked(false) ;
        checkBox_APLs_AddEdit_Questionnaires_Delete->setChecked(false) ;
        checkBox_APLs_AddEdit_Questionnaires_Edit->setChecked(false) ;

        //Users
        checkBox_APLs_AddEdit_Users_View->setChecked(false) ;
        checkBox_APLs_AddEdit_Users_Add->setChecked(false) ;
        checkBox_APLs_AddEdit_Users_Delete->setChecked(false) ;
        checkBox_APLs_AddEdit_Users_Edit->setChecked(false) ;

        //Settings
        checkBox_APLs_AddEdit_Settings_View->setChecked(false) ;
        checkBox_APLs_AddEdit_Settings_Edit->setChecked(false) ;

        //Other
        checkBox_APLs_AddEdit_SearchDatabase->setChecked(false) ;
        checkBox_APLs_AddEdit_BackUp->setChecked(false) ;
        checkBox_APLs_AddEdit_Collaborate->setChecked(false) ;
        checkBox_APLs_AddEdit_Export->setChecked(false) ;
    }
    else
    {
        QItemSelectionModel *selectedModel = tableWidget_APLs_View->selectionModel() ;
        QModelIndexList indexOfRows = selectedModel->selectedRows() ;

        pushButton_APLs_AddEdit_Submit->setText("Update") ;
        lineEdit_APLs_AddEdit_Name->setEnabled(false) ;

        AccessPermissionList aplToBeEditted ;
        aplToBeEditted = accessPermissionLists.at(indexOfRows.at(0).row()) ;

        lineEdit_APLs_AddEdit_Name->setText(QString::fromStdString(aplToBeEditted.getName())) ;

        //Is Active
        checkBox_APLs_AddEdit_Active->setChecked(aplToBeEditted.getIsAccountActive()) ;

        //Research Topics
        checkBox_APLs_AddEdit_Research_Topics_View->setChecked(aplToBeEditted.getCanViewResearchTopics()) ;
        checkBox_APLs_AddEdit_Research_Topics_Add->setChecked(aplToBeEditted.getCanAddResearchTopics()) ;
        checkBox_APLs_AddEdit_Research_Topics_Edit->setChecked(aplToBeEditted.getCanRemoveResearchTopics()) ;
        checkBox_APLs_AddEdit_Research_Topics_Delete->setChecked(aplToBeEditted.getCanEditResearchTopics()) ;

        //Participants
        checkBox_APLs_AddEdit_Participants_View->setChecked(aplToBeEditted.getCanViewParticipants()) ;
        checkBox_APLs_AddEdit_Participants_Add->setChecked(aplToBeEditted.getCanAddParticipants()) ;
        checkBox_APLs_AddEdit_Participants_Edit->setChecked(aplToBeEditted.getCanRemoveParticipants()) ;
        checkBox_APLs_AddEdit_Participants_Delete->setChecked(aplToBeEditted.getCanEditParticipants()) ;

        //Questionnaires
        checkBox_APLs_AddEdit_Questionnaires_View->setChecked(aplToBeEditted.getCanViewQuestionnaires()) ;
        checkBox_APLs_AddEdit_Questionnaires_Add->setChecked(aplToBeEditted.getCanAddQuestionnaires()) ;
        checkBox_APLs_AddEdit_Questionnaires_Edit->setChecked(aplToBeEditted.getCanRemoveQuestionnaires()) ;
        checkBox_APLs_AddEdit_Questionnaires_Delete->setChecked(aplToBeEditted.getCanEditQuestionnaires()) ;

        //Users
        checkBox_APLs_AddEdit_Users_View->setChecked(aplToBeEditted.getCanViewUsers()) ;
        checkBox_APLs_AddEdit_Users_Add->setChecked(aplToBeEditted.getCanAddUsers()) ;
        checkBox_APLs_AddEdit_Users_Edit->setChecked(aplToBeEditted.getCanRemoveUsers()) ;
        checkBox_APLs_AddEdit_Users_Delete->setChecked(aplToBeEditted.getCanEditUsers()) ;

        //Settings
        checkBox_APLs_AddEdit_Settings_View->setChecked(aplToBeEditted.getCanViewSettings()) ;
        checkBox_APLs_AddEdit_Settings_Edit->setChecked(aplToBeEditted.getCanEditSettings()) ;

        //Other
        checkBox_APLs_AddEdit_SearchDatabase->setChecked(aplToBeEditted.getCanSearchDatabase()) ;
        checkBox_APLs_AddEdit_BackUp->setChecked(aplToBeEditted.getCanBackUp()) ;
        checkBox_APLs_AddEdit_Collaborate->setChecked(aplToBeEditted.getCanCollaborate()) ;
        checkBox_APLs_AddEdit_Export->setChecked(aplToBeEditted.getCanExport()) ;
    }

    showWidgetInMainWorkingStackedWidget(widget_APLs_AddEdit) ;
}

void ViewMainScreen::deleteAccessPermissionList()
{
    //Prepare Data to be written to Socket
    connection.setOutboundHeader("delxAPLs") ;

    //Get Selected Rows
    QItemSelectionModel *selectedModel = tableWidget_APLs_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    //Vector Array of APLs To Be Deleted
    std::vector<AccessPermissionList> aplsToBeDeleted ;

    //Get All APLs To Be Deleted From Rows
    for (int i = 0; i < indexOfRows.size(); i++)
    {
        aplsToBeDeleted.push_back(accessPermissionLists.at(indexOfRows.at(i).row())) ;
    }

    connection.setOutboundMessage(aplsToBeDeleted) ;

    //Write to Socket
    readyWrite() ;
}

void ViewMainScreen::pushButton_Menu_Primary_Button_Participants_clicked()
{
    hideSecondaryMenuButtons() ;
    hideTertiaryMenuButtons() ;

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Participants.at(i)->show() ;
    }
}

void ViewMainScreen::pushButton_Menu_Secondary_Button_Participants_clicked()
{
    hideTertiaryMenuButtons() ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Participants.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Participants.at(i)->show() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Participants_View_clicked()
{
    viewParticipantTableWidget() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Participants_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditParticipant() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Participants_Edit_clicked()
{
    QItemSelectionModel *selectedModel = tableWidget_Participants_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Participant may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditParticipant() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Participants_Remove_clicked()
{
    QMessageBox::StandardButton deleteParticipantMessageBoxButton ;
    deleteParticipantMessageBoxButton = QMessageBox::warning(this,
                                                             "Warning",
                                                             "Are you sure you wish to delete selected Participants(s)?",
                                                              QMessageBox::Yes | QMessageBox::No) ;

    if (deleteParticipantMessageBoxButton == QMessageBox::Yes)
    {
        deleteParticipant() ;
    }
}
void ViewMainScreen::pushButton_Participants_View_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditParticipant() ;
}

void ViewMainScreen::pushButton_Participants_View_Edit_clicked()
{
    QItemSelectionModel *selectedModel = tableWidget_Participants_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Participant may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditParticipant() ;
    }
}

void ViewMainScreen::pushButton_Participants_View_Delete_clicked()
{
    QMessageBox::StandardButton deleteParticipantMessageBoxButton ;
    deleteParticipantMessageBoxButton = QMessageBox::warning(this,
                                                             "Warning",
                                                             "Are you sure you wish to delete selected Participants(s)?",
                                                              QMessageBox::Yes | QMessageBox::No) ;

    if (deleteParticipantMessageBoxButton == QMessageBox::Yes)
    {
        deleteParticipant() ;
    }
}

void ViewMainScreen::tableWidget_Participants_View_Cell_clicked(const QModelIndex &index)
{
    tableWidget_Participants_View->selectRow(index.row()) ;
}

void ViewMainScreen::pushButton_Participants_AddEdit_Submit_clicked()
{

    if (userIsEditingNotAddingObject)
    {
        connection.setOutboundHeader("editPpt") ;
    }
    else
    {
       connection.setOutboundHeader("addPpt") ;
    }

    Participant participant ;

    participant.setParticipantID(label_Participants_AddEdit_ParticipantID_GeneratedID->text().toStdString()) ;
    participant.setForename(lineEdit_Participants_AddEdit_Participant_Forename->text().toStdString()) ;
    participant.setSurname(lineEdit_Participants_AddEdit_Participant_Surname->text().toStdString()) ;
    QDate date = dateEdit_Participants_AddEdit_DateOfBirth->date() ;
    participant.setDateOfBirth(date.toString("yyyyMMdd").toStdString()) ;
    participant.setSex(radioButton_Participants_AddEdit_Male->isChecked()) ;
    participant.setGuardianForename(lineEdit_Participants_AddEdit_Guardian_Forename->text().toStdString()) ;
    participant.setGuardianSurname(lineEdit_Participants_AddEdit_Guardian_Surname->text().toStdString()) ;
    participant.setContactHome(lineEdit_Participants_AddEdit_Contact_Home->text().toStdString()) ;
    participant.setContactWork(lineEdit_Participants_AddEdit_Contact_Work->text().toStdString()) ;
    participant.setContactMobile(lineEdit_Participants_AddEdit_Contact_Mobile->text().toStdString()) ;
    participant.setAddressLine1(lineEdit_Participants_AddEdit_Address_Line1->text().toStdString()) ;
    participant.setAddressLine2(lineEdit_Participants_AddEdit_Address_Line2->text().toStdString()) ;
    participant.setAddressLine3(lineEdit_Participants_AddEdit_Address_Line3->text().toStdString()) ;
    participant.setAddressLine4(lineEdit_Participants_AddEdit_Address_Line4->text().toStdString()) ;
    participant.setAddressPostCode(lineEdit_Participants_AddEdit_Address_PostCode->text().toStdString()) ;

    connection.setOutboundMessage(participant) ;

    readyWrite() ;
}

void ViewMainScreen::updateParticipantTableWidget()
{
    QStringList tableHeaders ;
    tableHeaders << "ID" << "Forename" << "Surname" << "Date Of Birth" << "Sex"
                 << "Guardian\nForename" << "Guardian\nSurname?"
                 << "Contact\nHome" << "Contact\nWork" << "Contact\nMobile"
                 << "House Name" << "Street" << "Town" << "County" << "Post Code" ;

    const int COLUMN_COUNT = tableHeaders.size() ;
    tableWidget_Participants_View->setColumnCount(COLUMN_COUNT);
    tableWidget_Participants_View->setRowCount(participants.size());

    tableWidget_Participants_View->setHorizontalHeaderLabels(tableHeaders) ;

    if (participants.size() > 0)
    {
        for (unsigned row = 0; row < participants.size(); row++)
        {
            Participant participant = participants.at(row) ;

            tableWidget_Participants_View->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getParticipantID()))) ;
            tableWidget_Participants_View->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getForename()))) ;
            tableWidget_Participants_View->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getSurname()))) ;
            QDate date = QDate::fromString(QString::fromStdString(participant.getDateOfBirth()), "yyyyMMdd") ;
            tableWidget_Participants_View->setItem(row, 3, new QTableWidgetItem(date.toString("d MMMM yyyy"))) ;
            if (participant.getSex())
            {
                tableWidget_Participants_View->setItem(row, 4, new QTableWidgetItem("Male")) ;
            }
            else
            {
                tableWidget_Participants_View->setItem(row, 4, new QTableWidgetItem("Female")) ;
            }
            tableWidget_Participants_View->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getGuardianForename()))) ;
            tableWidget_Participants_View->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getGuardianSurname()))) ;
            tableWidget_Participants_View->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getContactHome()))) ;
            tableWidget_Participants_View->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getContactWork()))) ;
            tableWidget_Participants_View->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getContactMobile()))) ;
            tableWidget_Participants_View->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getAddressLine1()))) ;
            tableWidget_Participants_View->setItem(row, 11, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getAddressLine2()))) ;
            tableWidget_Participants_View->setItem(row, 12, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getAddressLine3()))) ;
            tableWidget_Participants_View->setItem(row, 13, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getAddressLine4()))) ;
            tableWidget_Participants_View->setItem(row, 14, new QTableWidgetItem(QString::fromStdString(
                                                                            participant.getAddresssPostCode()))) ;
        }
    }
}

void ViewMainScreen::getAllParticipants()
{
    connection.setOutboundHeader("get*Ppts") ;
    readyWrite() ;
}

void ViewMainScreen::viewParticipantTableWidget()
{
    getAllParticipants() ;
}

void ViewMainScreen::viewAddEditParticipant()
{
    if (userIsEditingNotAddingObject)
    {
        QItemSelectionModel *selectedModel = tableWidget_Participants_View->selectionModel() ;
        QModelIndexList indexOfRows = selectedModel->selectedRows() ;

        Participant participantToBeEditted = participants.at(indexOfRows.at(0).row()) ;

        lineEdit_Participants_AddEdit_Participant_Forename->setText(QString::fromStdString(participantToBeEditted.getForename())) ;
        lineEdit_Participants_AddEdit_Participant_Surname->setText(QString::fromStdString(participantToBeEditted.getSurname())) ;
        label_Participants_AddEdit_ParticipantID_GeneratedID->setText(QString::fromStdString(participantToBeEditted.getParticipantID())) ;
        dateEdit_Participants_AddEdit_DateOfBirth->setDate(QDate::fromString(QString::fromStdString(participantToBeEditted.getDateOfBirth()), "yyyyMMdd")) ;
        radioButton_Participants_AddEdit_Male->setChecked(participantToBeEditted.getSex()) ;
        radioButton_Participants_AddEdit_Female->setChecked(participantToBeEditted.getSex()) ;
        lineEdit_Participants_AddEdit_Guardian_Forename->setText(QString::fromStdString(participantToBeEditted.getGuardianForename())) ;
        lineEdit_Participants_AddEdit_Guardian_Surname->setText(QString::fromStdString(participantToBeEditted.getGuardianSurname())) ;
        lineEdit_Participants_AddEdit_Contact_Home->setText(QString::fromStdString(participantToBeEditted.getContactHome())) ;
        lineEdit_Participants_AddEdit_Contact_Work->setText(QString::fromStdString(participantToBeEditted.getContactWork())) ;
        lineEdit_Participants_AddEdit_Contact_Mobile->setText(QString::fromStdString(participantToBeEditted.getContactMobile())) ;
        lineEdit_Participants_AddEdit_Address_Line1->setText(QString::fromStdString(participantToBeEditted.getAddressLine1())) ;
        lineEdit_Participants_AddEdit_Address_Line2->setText(QString::fromStdString(participantToBeEditted.getAddressLine2())) ;
        lineEdit_Participants_AddEdit_Address_Line3->setText(QString::fromStdString(participantToBeEditted.getAddressLine3())) ;
        lineEdit_Participants_AddEdit_Address_Line4->setText(QString::fromStdString(participantToBeEditted.getAddressLine4())) ;
        lineEdit_Participants_AddEdit_Address_PostCode->setText(QString::fromStdString(participantToBeEditted.getAddresssPostCode())) ;

        pushButton_Participants_AddEdit_Submit->setText("Edit") ;
    }
    else
    {
        lineEdit_Participants_AddEdit_Participant_Forename->setText("") ;
        lineEdit_Participants_AddEdit_Participant_Surname->setText("") ;

        //Generate New & Unused Participant ID
        QString participantID ;
        bool unusedParticipantID = false ;//WARNING
        Participant participant ;

        while (!unusedParticipantID)
        {
            participantID = generateRandomParticipantID() ;

            for (unsigned i = 0; i < participants.size(); i++)
            {
                participant = participants.at(i) ;

                if (participantID != QString::fromStdString(participant.getParticipantID()))
                {
                    unusedParticipantID = true ;
                }
            }

            //If there isn't a Participant to begin with
            unusedParticipantID = true ;
        }

        label_Participants_AddEdit_ParticipantID_GeneratedID->setText(participantID) ;
        dateEdit_Participants_AddEdit_DateOfBirth->setDate(QDate::currentDate()) ;
        radioButton_Participants_AddEdit_Male->setChecked(true) ;
        radioButton_Participants_AddEdit_Female->setChecked(false) ;
        lineEdit_Participants_AddEdit_Guardian_Forename->setText("") ;
        lineEdit_Participants_AddEdit_Guardian_Surname->setText("") ;
        lineEdit_Participants_AddEdit_Contact_Home->setText("") ;
        lineEdit_Participants_AddEdit_Contact_Work->setText("") ;
        lineEdit_Participants_AddEdit_Contact_Mobile->setText("") ;
        lineEdit_Participants_AddEdit_Address_Line1->setText("") ;
        lineEdit_Participants_AddEdit_Address_Line2->setText("") ;
        lineEdit_Participants_AddEdit_Address_Line3->setText("") ;
        lineEdit_Participants_AddEdit_Address_Line4->setText("") ;
        lineEdit_Participants_AddEdit_Address_PostCode->setText("") ;

        pushButton_Participants_AddEdit_Submit->setText("Add") ;
    }

    showWidgetInMainWorkingStackedWidget(widget_Participants_AddEdit) ;
}

QString ViewMainScreen::generateRandomParticipantID()
{
    QString randomParticipantID ;
    randomParticipantID = "pp" ;

    int randomNumber ;
    randomNumber = rand() % 10000 + 1 ;

    //Ensure A Correct Number is Generated
    while (!(randomNumber > 1) && !(randomNumber < 10000))
    {
        randomNumber = rand() % 1000 + 1 ;
    }

    //Ensure 4 figure length
    if (randomNumber < 10)
    {
        randomParticipantID.append("000") ;
    }
    else if (randomNumber < 100 && randomNumber >= 10)
    {
        randomParticipantID.append("00") ;
    }
    else if (randomNumber < 1000 && randomNumber >= 100)
    {
        randomParticipantID.append("0") ;
    }

    randomParticipantID.append(QString::number(randomNumber)) ;
    randomParticipantID.append("    ") ;

    return randomParticipantID ;
}

void ViewMainScreen::deleteParticipant()
{
    //Prepare Data to be written to Socket
    this->connection.setOutboundHeader("delxPpts") ;

    //Get Selected Rows
    QItemSelectionModel *selectedModel = tableWidget_Participants_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    //Vector Array of Participants To Be Deleted
    std::vector<Participant> participantsToBeDeleted ;

    //Get All Participants To Be Deleted From Rows
    for (int i = 0; i < indexOfRows.size(); i++)
    {
        participantsToBeDeleted.push_back(participants.at(indexOfRows.at(i).row())) ;
    }

    connection.setOutboundMessage(participantsToBeDeleted) ;

    //Write to Socket
    readyWrite() ;
}

void ViewMainScreen::pushButton_Menu_Primary_Button_Home_clicked()
{
    hideSecondaryMenuButtons() ;
    hideTertiaryMenuButtons() ;

    showWidgetInMainWorkingStackedWidget(widget_Home) ;
}

void ViewMainScreen::pushButton_Menu_Primary_Button_Questionnaires_clicked()
{
    hideSecondaryMenuButtons() ;
    hideTertiaryMenuButtons() ;

    for (int i = 0; i < pushButton_Menu_Secondary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Secondary_Buttons_Questionnaires.at(i)->show() ;
    }
}

void ViewMainScreen::pushButton_Menu_Secondary_Button_Questionnaires_clicked()
{
    hideTertiaryMenuButtons() ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Questionnaires.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Questionnaires.at(i)->show() ;
    }
}

void ViewMainScreen::pushButton_Menu_Secondary_Button_Questions_clicked()
{
    hideTertiaryMenuButtons() ;

    for (int i = 0; i < pushButton_Menu_Tertiary_Buttons_Questions.size(); i++)
    {
        pushButton_Menu_Tertiary_Buttons_Questions.at(i)->show() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Questionnaire_View_clicked()
{
    viewQuestionnaireTableWidget() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Questionnaire_Add_clicked()
{
    userIsEditingNotAddingObject = false ;

    viewAddEditQuestionnaire() ;
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Questionnaire_Edit_clicked()
{
    //Get Selected Row
    QItemSelectionModel *selectedModel = tableWidget_Questionnaires_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Questionnaire may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditQuestionnaire() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Questionnaire_Remove_clicked()
{
    QMessageBox::StandardButton deleteQuestionnaireMessageBoxButton ;
    deleteQuestionnaireMessageBoxButton = QMessageBox::warning(this,
                                 "Warning",
                                 "Are you sure you wish to delete selected Questionnaires(s)?",
                                  QMessageBox::Yes | QMessageBox::No) ;

    if (deleteQuestionnaireMessageBoxButton == QMessageBox::Yes)
    {
        deleteQuestionnaire() ;
    }
}

void ViewMainScreen::pushButton_Menu_Tertiary_Button_Questions_View_clicked()
{
    qDebug() << "3 - Questions - View clicked" ;
    //showWidgetInMainWorkingStackedWidget(widget_Questions_View) ;
}

void ViewMainScreen::pushButton_Menu_Primary_Button_Lock_clicked()
{
    userLoggedIn = true ;

    lineEdit_Login_Username->setText(QString::fromStdString(currentUser.getUserId())) ;
    lineEdit_Login_Password->setText("") ;

    lineEdit_Login_Username->setEnabled(false) ;

    showFrameLockScreen(true) ;
    showFrameLoginScreen(true) ;
}

void ViewMainScreen::pushButton_Menu_Primary_Button_Logout_clicked()
{
    //Clear Screen
//    showWidgetInMainWorkingStackedWidget() ;
    hideSecondaryMenuButtons() ;
    hideTertiaryMenuButtons() ;

    userLoggedIn = false ;

    lineEdit_Login_Username->setText("") ;
    lineEdit_Login_Password->setText("") ;

    lineEdit_Login_Username->setEnabled(true) ;

    showFrameLockScreen(true) ;
    showFrameLoginScreen(true) ;

    //Empty Vectors for next User
    users.clear() ;
    accessPermissionLists.clear() ;
    participants.clear() ;
    questionnaires.clear() ;
}

void ViewMainScreen::pushButton_Questionnaires_View_Add_clicked()
{
    this->userIsEditingNotAddingObject = false ;

    viewAddEditQuestionnaire() ;
}

void ViewMainScreen::pushButton_Questionnaires_View_Edit_clicked()
{
    //Get Selected Row
    QItemSelectionModel *selectedModel = tableWidget_Questionnaires_View->selectionModel() ;
    QModelIndexList indexOfRows = selectedModel->selectedRows() ;

    if (indexOfRows.size() != 1)
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Only 1 Questionnaire may be editted at a time.",
                             QMessageBox::Ok) ;
    }
    else
    {
        userIsEditingNotAddingObject = true ;

        viewAddEditQuestionnaire() ;
    }
}

void ViewMainScreen::pushButton_Questionnaires_View_Delete_clicked()
{
    QMessageBox::StandardButton deleteQuestionnaireMessageBoxButton ;
    deleteQuestionnaireMessageBoxButton = QMessageBox::warning(this,
                                 "Warning",
                                 "Are you sure you wish to delete selected Questionnaires(s)?",
                                  QMessageBox::Yes | QMessageBox::No) ;

    if (deleteQuestionnaireMessageBoxButton == QMessageBox::Yes)
    {
        deleteQuestionnaire() ;
    }
}

void ViewMainScreen::pushButton_Questionnaires_AddEdit_Submit_clicked()
{
    if (questionnaireAddEdit.getQuestions().size() > 0)
    {
        if (userIsEditingNotAddingObject)
        {
            connection.setOutboundHeader("editQues") ;
        }
        else
        {
            connection.setOutboundHeader("addQues") ;
        }

        questionnaireAddEdit.setQuestionnaireID(label_Questionnaires_AddEdit_Title_ID->text().toStdString()) ;
        questionnaireAddEdit.setNote(lineEdit_Questionnaires_AddEdit_Note->text().toStdString()) ;

        //Ensure Correct Question Numbers
        for (unsigned i = 0; i < questionnaireAddEdit.getQuestions().size(); i++)
        {
            questionnaireAddEdit.getQuestions().at(i)->setQNumber(i) ;
        }

        //Set Outbound Message
        connection.setOutboundMessage(questionnaireAddEdit) ;

        //Write to Socket
        readyWrite() ;
    }
    else
    {
        QMessageBox::warning(this,
                             "Warning",
                             "No Questions in the Questionnaire.",
                             QMessageBox::Ok) ;
    }
}

void ViewMainScreen::pushButton_Questionnaires_AddEdit_AddLine_clicked()
{
    if (questionnaireAddEdit.getQuestionCount() < 10)
    {
        if (!lineEdit_Questionnaires_AddEdit_Question->text().isEmpty())
        {
            if (comboBox_Questionnaires_AddEdit_New_Question_Question_Type->currentText() == "Boolean")
            {
                BooleanQuestion *booleanQuestion = new BooleanQuestion() ;

                booleanQuestion->setQuestion(lineEdit_Questionnaires_AddEdit_Question->text().toStdString()) ;

                booleanQuestion->setQuestionID(generateRandomQuestionID("boolean")) ;

                questionnaireAddEdit.addQuestion(booleanQuestion) ;
            }
            else if (comboBox_Questionnaires_AddEdit_New_Question_Question_Type->currentText() == "Text")
            {
                TextQuestion *textQuestion = new TextQuestion() ;

                textQuestion->setQuestion(lineEdit_Questionnaires_AddEdit_Question->text().toStdString()) ;

                textQuestion->setQuestionID(generateRandomQuestionID("text")) ;

                questionnaireAddEdit.addQuestion(textQuestion) ;
            }
            else if (comboBox_Questionnaires_AddEdit_New_Question_Question_Type->currentText() == "Number")
            {
                NumberQuestion *numberQuestion = new NumberQuestion() ;

                numberQuestion->setQuestion(lineEdit_Questionnaires_AddEdit_Question->text().toStdString()) ;

                if (!lineEdit_Questionnaires_AddEdit_Question_Range_Base->text().isEmpty())
                {
                    numberQuestion->setBase(lineEdit_Questionnaires_AddEdit_Question_Range_Base->text().toInt()) ;
                }
                else
                {
                    numberQuestion->setBase(0) ;
                }

                if (!lineEdit_Questionnaires_AddEdit_Question_Range_Range->text().isEmpty())
                {
                    numberQuestion->setRange(lineEdit_Questionnaires_AddEdit_Question_Range_Range->text().toInt()) ;
                }
                else
                {
                    numberQuestion->setRange(0) ;
                }

                numberQuestion->setQuestionID(generateRandomQuestionID("number")) ;

                questionnaireAddEdit.addQuestion(numberQuestion) ;
            }

            addNewQuestionToAddEditViewList(questionnaireAddEdit.getQuestions().at(questionnaireAddEdit.getQuestionCount() -1)) ;
        }
        else
        {
            QMessageBox::warning(this,
                                 "Warning",
                                 "Must have a question to ask participant!",
                                 QMessageBox::Ok) ;
        }
    }
    else
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Reached Questionnaire question limit of 10!",
                             QMessageBox::Ok) ;
    }
}

void ViewMainScreen::comboBox_Questionnaires_AddEdit_New_Question_Question_Type_clicked(QString title)
{
    if (title == "Number")
    {
        lineEdit_Questionnaires_AddEdit_Question_Range_Base->setEnabled(true) ;
        lineEdit_Questionnaires_AddEdit_Question_Range_Range->setEnabled(true) ;
    }
    else
    {
        lineEdit_Questionnaires_AddEdit_Question_Range_Base->setEnabled(false) ;
        lineEdit_Questionnaires_AddEdit_Question_Range_Range->setEnabled(false) ;
    }
}

void ViewMainScreen::pushButton_Questionnaires_AddEdit_Remove_Question_clicked(QString title)
{
    removeQuestionFromAddEditViewList(title) ;
}

void ViewMainScreen::updateQuestionnaireTableWidget()
{
    QStringList tableHeaders ;
    tableHeaders << "ID" << "Question 1" << "Question 2" << "Question 3" << "Question 4" << "Question 5"
                     << "Question 6" << "Question 7" << "Question 8" << "Question 9" << "Question 10" ;

    const int COLUMN_COUNT = tableHeaders.size() ;
    tableWidget_Questionnaires_View->setColumnCount(COLUMN_COUNT);
    tableWidget_Questionnaires_View->setRowCount(questionnaires.size());

    tableWidget_Questionnaires_View->setHorizontalHeaderLabels(tableHeaders) ;

    for (unsigned row = 0; row < questionnaires.size(); row++)
    {
        tableWidget_Questionnaires_View->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(
                                                                         questionnaires.at(row).getQuestionnaireID()))) ;

        for (unsigned column = 0; column < questionnaires.at(row).getQuestions().size(); column++)
        {
            tableWidget_Questionnaires_View->setItem(row, column+1, new QTableWidgetItem(QString::fromStdString(
                                                                                             questionnaires.at(row).
                                                                                             getQuestions().at(column)->
                                                                                             getQuestion()))) ;
        }
    }
}

void ViewMainScreen::getAllQuestionnaires()
{
    connection.setOutboundHeader("get*Ques") ;
    readyWrite() ;
}

void ViewMainScreen::viewQuestionnaireTableWidget()
{
    getAllQuestionnaires() ;
}

void ViewMainScreen::viewAddEditQuestionnaire()
{
    clearQuestionsFromAddEditViewList() ;

    if (!userIsEditingNotAddingObject) //Adding
    {
        //Clear the AddEdit Questionnaire
        while (questionnaireAddEdit.getQuestionCount() != 0)
        {
            questionnaireAddEdit.removeQuestionAtLocation(-1) ; //Pop-back
        }

        label_Questionnaires_AddEdit_Title_ID->setText("Please Wait...") ;

        //Generate New & Unused Questionnaire ID //WARNING - should be in a thread
        QString questionnaireID ;
        bool unusedQuestionnaireID = false ;//WARNING

        while (!unusedQuestionnaireID)
        {
            questionnaireID = generateRandomQuestionnaireID() ;

            for (unsigned i = 0; i < questionnaires.size(); i++)
            {
                if (questionnaireID != QString::fromStdString(questionnaires.at(i).getQuestionnaireID()))
                {
                    label_Questionnaires_AddEdit_Title_ID->setText(questionnaireID) ;

                    unusedQuestionnaireID = true ;
                }
            }
        }

        lineEdit_Questionnaires_AddEdit_Note->setText("") ;

        pushButton_Questionnaires_AddEdit_Submit->setText("Add") ;
    }
    else //Editing
    {
        //Get Selected Row
        QItemSelectionModel *selectedModel = tableWidget_Questionnaires_View->selectionModel() ;
        QModelIndexList indexOfRows = selectedModel->selectedRows() ;

        questionnaireAddEdit = questionnaires.at(indexOfRows.at(0).row()) ;

        label_Questionnaires_AddEdit_Title_ID->setText(QString::fromStdString(questionnaireAddEdit.getQuestionnaireID())) ;
        lineEdit_Questionnaires_AddEdit_Note->setText(QString::fromStdString(questionnaireAddEdit.getNote()));

        if (questionnaireAddEdit.getQuestionCount() > 0)
        {
            for (int i = 0; i < questionnaireAddEdit.getQuestionCount(); i++)
            {
                addQuestionToAddEditViewList(questionnaireAddEdit.getQuestions().at(i)) ;
            }
        }

        pushButton_Questionnaires_AddEdit_Submit->setText("Edit") ;
    }

    showWidgetInMainWorkingStackedWidget(widget_Questionnaires_AddEdit) ;
}

QString ViewMainScreen::generateRandomQuestionnaireID()
{
    QString randomQuestionnaireID ;
    randomQuestionnaireID = "qu" ;

    int randomNumber ;
    randomNumber = rand() % 10000 + 1 ;

    //Ensure A Correct Number is Generated
    while (!(randomNumber > 1) && !(randomNumber < 10000))
    {
        randomNumber = rand() % 1000 + 1 ;
    }

    //Ensure 4 figure length
    if (randomNumber < 10)
    {
        randomQuestionnaireID.append("000") ;
    }
    else if (randomNumber < 100 && randomNumber >= 10)
    {
        randomQuestionnaireID.append("00") ;
    }
    else if (randomNumber < 1000 && randomNumber >= 100)
    {
        randomQuestionnaireID.append("0") ;
    }

    randomQuestionnaireID.append(QString::number(randomNumber)) ;
    randomQuestionnaireID.append("    ") ;

    return randomQuestionnaireID ;
}

QString ViewMainScreen::generateRandomQuestionID(QString type)
{
    QString randomQuestionID ;

    if (type == "boolean")
    {
        randomQuestionID = "qb" ;
    }
    else if (type == "number")
    {
        randomQuestionID = "qn" ;
    }
    else if (type == "text")
    {
        randomQuestionID = "qt" ;
    }

    int randomNumber ;
    randomNumber = rand() % 10000 + 1 ;

    //Ensure A Correct Number is Generated
    while (!(randomNumber > 1) && !(randomNumber < 10000))
    {
        randomNumber = rand() % 1000 + 1 ;
    }

    //Ensure 4 figure length
    if (randomNumber < 10)
    {
        randomQuestionID.append("000") ;
    }
    else if (randomNumber < 100 && randomNumber >= 10)
    {
        randomQuestionID.append("00") ;
    }
    else if (randomNumber < 1000 && randomNumber >= 100)
    {
        randomQuestionID.append("0") ;
    }

    randomQuestionID.append(QString::number(randomNumber)) ;
    randomQuestionID.append("    ") ;

    return randomQuestionID ;
}

void ViewMainScreen::deleteQuestionnaire()
{

}

void ViewMainScreen::tableWidget_Questionnaires_View_Cell_clicked(const QModelIndex &index)
{
    tableWidget_Questionnaires_View->selectRow(index.row()) ;
}

void ViewMainScreen::addNewQuestionToAddEditViewList(Question *question)
{
    QString labelTitle ;
    labelTitle.append("Question: ") ;
    labelTitle.append(lineEdit_Questionnaires_AddEdit_Question->text()) ;
    labelTitle.append("(") ;
    labelTitle.append(comboBox_Questionnaires_AddEdit_New_Question_Question_Type->currentText()) ;
    labelTitle.append(")") ;

    showQuestionInAddEditViewList(labelTitle, question) ;
}

void ViewMainScreen::removeQuestionFromAddEditViewList(QString /*title*/)
{
    questionnaireAddEdit.removeQuestionAtLocation(-1) ;

    clearQuestionsFromAddEditViewList() ;

    label_Questionnaires_Questions.clear() ;
    pushButton_Questionnaires_Remove_Buttons.clear() ;

    if (questionnaireAddEdit.getQuestionCount() > 0)
    {
        for (int i = 0; i < questionnaireAddEdit.getQuestionCount(); i++)
        {
            addQuestionToAddEditViewList(questionnaireAddEdit.getQuestions().at(i)) ;
        }
    }
}

void ViewMainScreen::showQuestionInAddEditViewList(QString labelTitle, Question* question)
{
    QWidget *widget_Question = new QWidget() ;
    QHBoxLayout *layout_Question = new QHBoxLayout(widget_Question) ;
    QLabel *label_Question = new QLabel(labelTitle, widget_Question) ;
    QPushButton *pushButton_RemoveQuestion = new QPushButton("Remove Q", widget_Question) ;

    widget_Question->setLayout(layout_Question) ;

    QString stringButtonText = "Remove Q" ;
    stringButtonText.append(QString::number(question->getQNumber()+1)) ;
    pushButton_RemoveQuestion->setText(stringButtonText) ;

    layout_Question->addWidget(label_Question) ;
    layout_Question->addStretch() ;
    layout_Question->addWidget(pushButton_RemoveQuestion) ;

    connect(pushButton_RemoveQuestion, SIGNAL(clicked()),
            signalMapperQuestionnaireAddEdit, SLOT(map())) ;

    signalMapperQuestionnaireAddEdit->setMapping(pushButton_RemoveQuestion,
                                                 pushButton_RemoveQuestion->text()) ;

    /*
     * Add to Arrays
     */
    //Widget
    widget_Question->show() ;
    widget_Questionnaires_Questions.push_back(widget_Question) ;
    //Label
    label_Questionnaires_Questions.push_back(label_Question) ;
    //PushButton
    pushButton_Questionnaires_Remove_Buttons.push_back(pushButton_RemoveQuestion) ;

    //Hide all buttons except last
    for (int i = 0; i < pushButton_Questionnaires_Remove_Buttons.size()-1; i++)
    {
        pushButton_Questionnaires_Remove_Buttons.at(i)->hide() ;
    }

    //Present Layout
    layout_Vertical_Questionnaires_AddEdit_Questions->addWidget(widget_Questionnaires_Questions.at(widget_Questionnaires_Questions.size()-1)) ;
}

void ViewMainScreen::addQuestionToAddEditViewList(Question *question)
{
    QString labelTitle ;
    labelTitle.append("Question: ") ;

    if (dynamic_cast<BooleanQuestion *>(question) != nullptr)
    {
        labelTitle.append(QString::fromStdString(question->getQuestion())) ;
        labelTitle.append("(Boolean)") ;
    }
    else if (dynamic_cast<NumberQuestion *>(question) != nullptr)
    {
        labelTitle.append(QString::fromStdString(question->getQuestion())) ;
        labelTitle.append("(Number)") ;
    }
    else if (dynamic_cast<TextQuestion *>(question) != nullptr)
    {
        labelTitle.append(QString::fromStdString(question->getQuestion())) ;
        labelTitle.append("(Text)") ;
    }

    showQuestionInAddEditViewList(labelTitle, question) ;
}

void ViewMainScreen::clearQuestionsFromAddEditViewList()
{
    //Widgets
    for (int i = 0; i < widget_Questionnaires_Questions.size(); i++)
    {
        layout_Vertical_Questionnaires_AddEdit_Questions->removeWidget(widget_Questionnaires_Questions.at(i)) ;//->deleteLater() ;
        widget_Questionnaires_Questions.at(i)->hide() ;
    }

    //PushButton
    for (int i = 0; i < pushButton_Questionnaires_Remove_Buttons.size(); i++)
    {
        pushButton_Questionnaires_Remove_Buttons.at(i)->removeEventFilter(this) ;
        pushButton_Questionnaires_Remove_Buttons.at(i)->deleteLater();
        pushButton_Questionnaires_Remove_Buttons.pop_back() ;
    }

    //Label
    for (int i = 0; i < label_Questionnaires_Questions.size(); i++)
    {
        label_Questionnaires_Questions.at(i)->hide() ;
        label_Questionnaires_Questions.at(i)->deleteLater() ;
        label_Questionnaires_Questions.pop_back() ;
    }

    label_Questionnaires_Questions.clear() ;
    pushButton_Questionnaires_Remove_Buttons.clear() ;
}
