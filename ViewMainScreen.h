#ifndef VIEWMAINSCREEN_H
#define VIEWMAINSCREEN_H

#include <QDebug>

/*
 * Qt GUI
 */
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QStackedWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>
#include <QDateEdit>

/*
 * C++ Classes
 */
#include <string>
#include <vector>

/*
 * Qt's (C++) Classes
 */
#include <QString>
#include <QVector>
#include <QDate>
#include <QUrl>
#include <QSignalMapper>

/*
 * Project Classes
 */
#include "Login.h"
#include "AccessPermissionList.h"
#include "Person.h"
#include "User.h"
#include "Participant.h"
#include "Questionnaire.h"
#include "Question.h"
#include "BooleanQuestion.h"
#include "NumberQuestion.h"
#include "TextQuestion.h"

/*
 * Server & Networking
 */
#include "Connection.h"
#include "ServerInformation.h"

#include <QTcpSocket>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include <QNetworkConfiguration>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

namespace Ui {
class ViewMainScreen;
}

class ViewMainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewMainScreen(QWidget *parent = 0);
    ~ViewMainScreen();

public slots:
    void readyRead() ;

signals:
    void clicked(QString) ;

private:
    Ui::ViewMainScreen *ui ;

    /*
     * Bootstaps
     */
    void viewDidLoad() ;
    void initObjects() ; //Initialize Objects
    void initGUI() ;
    void connectSignalsAndSlots() ; //Connect Signals & Slots

    /*
     * Global Variables
     */
    std::vector<AccessPermissionList> accessPermissionLists ;
    std::vector<User> users ;
    std::vector<Participant> participants ;
    std::vector<Questionnaire> questionnaires ;

    /*
     * User
     */
    User currentUser ;
    bool userLoggedIn ;

    /*
     * Server Connection
     */
    void setNetworkConection() ;
    QTcpSocket *socket ;
    QByteArray buffer ;
    Connection connection ;
    QString incomingMessage ;
    void readyWrite() ;

    /*
     * Const Sizes / Variables
     */
    int TITLE_HEIGHT ;

    int MAIN_MENU_PADDING  ;

    int PRIMARY_BUTTON_WIDTH  ;
    int PRIMARY_BUTTON_HEIGHT  ;
    int PRIMARY_BUTTON_GRADIENT  ;

    int SECONDARY_BUTTON_WIDTH  ;
    int SECONDARY_BUTTON_HEIGHT  ;
    int SECONDARY_BUTTON_GRADIENT  ;

    int LOGIN_FRAME_WIDTH ;
    int LOGIN_FRAME_HEIGHT ;

    /*
     * Lock Frame
     */
    QFrame *frame_LockScreen ;
    void initFrame_LockScreen() ;
    void showFrameLockScreen(bool show) ;

    /*
     * Login Frame
     */
    QFrame *frame_LoginScreen ;
    QGridLayout *gridLayout_Login ;
    QLineEdit *lineEdit_Login_Username ;
    QLineEdit *lineEdit_Login_Password ;
    QPushButton *pushButton_Login_Login ;
    void initFrame_LoginScreen() ;
    void showFrameLoginScreen(bool show) ;
    void loginAttempt() ;
    void loginSuccessful(User user) ;
    void loginFailed() ;

    /*
     * Status Bar
     */
    //void setUIStatusBar() ;

    /*
     * Main Working Area - Frame, Widget, Tables etc
     */
    //Title
    QLabel *label_Window_Title ;

    //Frame (+ Border)
    QFrame *frame_MainWorkingAreaBorder ;
    QFrame *frame_MainWorkingArea ;

    /*
     * Stacked Widget
     */
    void initStackedWidget_MainWorkingArea() ;
    QStackedWidget *stackedWidget_MainWorkingArea ;
    bool userIsEditingNotAddingObject ;
    void showWidgetInMainWorkingStackedWidget(QWidget *widget) ;
    void initFrame_MainWorkingArea() ;

    /*
     * Widget - Home
     */
    void initWidget_Home() ;
    QWidget *widget_Home ;
    QVBoxLayout *layout_Vertical_Home ;
    QHBoxLayout *layout_Horizontal_Home ;

    /*
     * Widget - Users View
     */
    void initWidget_Users_View() ;
    QWidget *widget_Users_View ;
    QVBoxLayout *layout_Vertical_Users_View ;
    QHBoxLayout *layout_Horizontal_Users_View ;
    QTableWidget *tableWidget_Users_View ;
    QPushButton *pushButton_Users_View_Add ;
    QPushButton *pushButton_Users_View_Edit ;
    QPushButton *pushButton_Users_View_Delete ;

    /*
     * Widget - Users Add/Edit
     */
    void initWidget_Users_AddEdit() ;
    QWidget *widget_Users_AddEdit ;
    QVBoxLayout *layout_Vertical_Users_AddEdit ;
    QHBoxLayout *layout_Horizontal_Users_AddEdit ;
    QHBoxLayout *layout_Horizontal_Users_AddEdit_Buttons ;
    QFormLayout *layout_Form_Users_AddEdit_Form ;
    QLabel *label_Users_AddEdit_UserID ;
    QLabel *label_Users_AddEdit_UserID_Generated_ID ;
    QLabel *label_Users_AddEdit_Password ;
    QLabel *label_Users_AddEdit_Password_Default_Password ;
    QLabel *label_Users_AddEdit_Forename ;
    QLineEdit *lineEdit_Users_AddEdit_Forename ;
    QLabel *label_Users_AddEdit_Surname ;
    QLineEdit *lineEdit_Users_AddEdit_Surname ;
    QLabel *label_Users_AddEdit_Department ;
    QLineEdit *lineEdit_Users_AddEdit_Department ;
    QLabel *label_Users_AddEdit_Role ;
    QLineEdit *lineEdit_Users_AddEdit_Role ;
    QLabel *label_Users_AddEdit_APL ;
    QComboBox *comboBox_Users_AddEdit_APL ;
    QLabel *label_Users_AddEdit_AccountActive ;
    QCheckBox *checkBox_Users_AddEdit_AccountActive ;
    QPushButton *pushButton_Users_AddEdit_Submit ;

    /*
     * Functions - Users
     */
    void updateUserTableWidget() ;
    void getAllUsers() ;
    void viewUserTableWidget() ;
    void viewAddEditUser() ;
    QString generateRandomUsername() ;
    void loadUserAddEditAccessPermissionListComboBox() ;
    void deleteUser() ;

    /*
     * Widget - APLs View
     */
    void initWidget_APLs_View() ;
    QWidget *widget_APLs_View ;
    QVBoxLayout *layout_Vertical_APLs_View ;
    QHBoxLayout *layout_Horizontal_APLs_View ;
    QTableWidget *tableWidget_APLs_View ;
    QPushButton *pushButton_APLs_View_Add ;
    QPushButton *pushButton_APLs_View_Edit ;
    QPushButton *pushButton_APLs_View_Delete ;

    /*
     * Widget - APLs Add/Edit
     */
    void initWidget_APLs_AddEdit() ;
    QWidget *widget_APLs_AddEdit ;
    QVBoxLayout *layout_APLs_AddEdit ;
    QHBoxLayout *layout_APLs_AddEdit_TitleActive ;
    QHBoxLayout *layout_APLs_AddEdit_Title ;
    QHBoxLayout *layout_APLs_AddEdit_Active ;
    QHBoxLayout *layout_APLs_AddEdit_CheckBoxes ;
    QVBoxLayout *layout_APLs_AddEdit_CheckBoxes_ColumnA ;
    QVBoxLayout *layout_APLs_AddEdit_CheckBoxes_ColumnB ;
    QHBoxLayout *layout_APLs_AddEdit_Button ;
    QLabel *label_APLs_AddEdit_Name ;
    QLineEdit *lineEdit_APLs_AddEdit_Name ;
    QCheckBox *checkBox_APLs_AddEdit_Active ;
    QLabel *label_APLs_AddEdit_Research_Topics ;
    QCheckBox *checkBox_APLs_AddEdit_Research_Topics_View ;
    QCheckBox *checkBox_APLs_AddEdit_Research_Topics_Add ;
    QCheckBox *checkBox_APLs_AddEdit_Research_Topics_Edit ;
    QCheckBox *checkBox_APLs_AddEdit_Research_Topics_Delete ;
    QLabel *label_APLs_AddEdit_Participants ;
    QCheckBox *checkBox_APLs_AddEdit_Participants_View ;
    QCheckBox *checkBox_APLs_AddEdit_Participants_Add ;
    QCheckBox *checkBox_APLs_AddEdit_Participants_Edit ;
    QCheckBox *checkBox_APLs_AddEdit_Participants_Delete ;
    QLabel *label_APLs_AddEdit_Questionnaires ;
    QCheckBox *checkBox_APLs_AddEdit_Questionnaires_View ;
    QCheckBox *checkBox_APLs_AddEdit_Questionnaires_Add ;
    QCheckBox *checkBox_APLs_AddEdit_Questionnaires_Edit ;
    QCheckBox *checkBox_APLs_AddEdit_Questionnaires_Delete ;
    QLabel *label_APLs_AddEdit_Users ;
    QCheckBox *checkBox_APLs_AddEdit_Users_View ;
    QCheckBox *checkBox_APLs_AddEdit_Users_Add ;
    QCheckBox *checkBox_APLs_AddEdit_Users_Edit ;
    QCheckBox *checkBox_APLs_AddEdit_Users_Delete ;
    QLabel *label_APLs_AddEdit_Other ;
    QCheckBox *checkBox_APLs_AddEdit_SearchDatabase ;
    QCheckBox *checkBox_APLs_AddEdit_BackUp ;
    QCheckBox *checkBox_APLs_AddEdit_Collaborate ;
    QCheckBox *checkBox_APLs_AddEdit_Export ;
    QLabel *label_APLs_AddEdit_Settings ;
    QCheckBox *checkBox_APLs_AddEdit_Settings_View ;
    QCheckBox *checkBox_APLs_AddEdit_Settings_Edit ;
    QPushButton *pushButton_APLs_AddEdit_Submit ;

    /*
     * Functions - Access Permission Lists
     */
    void updateAPLTableWidget() ;
    void getAllAccessPermissionLists() ;
    void viewAccessPermissionListTableWidget() ;
    void viewAddEditAccessPermissionList() ;
    void deleteAccessPermissionList() ;//

    /*
     * Widget - View Participants
     */
    void initWidget_Participants_View() ;
    QWidget *widget_Participants_View ;
    QVBoxLayout *layout_Vertical_Participants_View ;
    QHBoxLayout *layout_Horizontal_Participants_View ;
    QTableWidget *tableWidget_Participants_View ;
    QPushButton *pushButton_Participants_View_Add ;
    QPushButton *pushButton_Participants_View_Edit ;
    QPushButton *pushButton_Participants_View_Delete ;

    /*
     * Widget - Add/Edit Participants
     */
    void initWidget_Participants_AddEdit() ;
    QWidget *widget_Participants_AddEdit ;
    QVBoxLayout *layout_Participants_AddEdit ;
    QVBoxLayout *layout_Vertical_Participants_AddEdit ;
    QHBoxLayout *layout_Horizontal_Participants_AddEdit ;
    QHBoxLayout *layout_Horizontal_Participants_AddEdit_Buttons ;
    QFormLayout *layout_Form_Participants_AddEdit_Form ;
    QLabel *label_Participants_AddEdit_Participant_Title ;
    QLabel *label_Participants_AddEdit_Participant_Forename ;
    QLineEdit *lineEdit_Participants_AddEdit_Participant_Forename ;
    QLabel *label_Participants_AddEdit_Participant_Surname ;
    QLineEdit *lineEdit_Participants_AddEdit_Participant_Surname ;
    QLabel *label_Participants_AddEdit_ParticipantID ;
    QLabel *label_Participants_AddEdit_ParticipantID_GeneratedID ;
    QLabel *label_Participants_AddEdit_DateOfBirth ;
    QDateEdit *dateEdit_Participants_AddEdit_DateOfBirth ;
    QLabel *label_Participants_AddEdit_Sex ;
    QRadioButton *radioButton_Participants_AddEdit_Male ;
    QRadioButton *radioButton_Participants_AddEdit_Female ;
    QLabel *label_Participants_AddEdit_Guardian_Title ;
    QLabel *label_Participants_AddEdit_Guardian_Forename ;
    QLineEdit *lineEdit_Participants_AddEdit_Guardian_Forename ;
    QLabel *label_Participants_AddEdit_Guardian_Surname ;
    QLineEdit *lineEdit_Participants_AddEdit_Guardian_Surname ;
    QLabel *label_Participants_AddEdit_Contact_Title ;
    QLabel *label_Participants_AddEdit_Contact_Home ;
    QLineEdit *lineEdit_Participants_AddEdit_Contact_Home ;
    QLabel *label_Participants_AddEdit_Contact_Work ;
    QLineEdit *lineEdit_Participants_AddEdit_Contact_Work ;
    QLabel *label_Participants_AddEdit_Contact_Mobile ;
    QLineEdit *lineEdit_Participants_AddEdit_Contact_Mobile ;
    QLabel *label_Participants_AddEdit_Address_Title ;
    QLabel *label_Participants_AddEdit_Address_Line1 ;
    QLineEdit *lineEdit_Participants_AddEdit_Address_Line1 ;
    QLabel *label_Participants_AddEdit_Address_Line2 ;
    QLineEdit *lineEdit_Participants_AddEdit_Address_Line2 ;
    QLabel *label_Participants_AddEdit_Address_Line3 ;
    QLineEdit *lineEdit_Participants_AddEdit_Address_Line3 ;
    QLabel *label_Participants_AddEdit_Address_Line4 ;
    QLineEdit *lineEdit_Participants_AddEdit_Address_Line4 ;
    QLabel *label_Participants_AddEdit_Address_PostCode ;
    QLineEdit *lineEdit_Participants_AddEdit_Address_PostCode ;
    QPushButton *pushButton_Participants_AddEdit_Submit ;

    /*
     * Functions - Participants
     */
    void updateParticipantTableWidget() ;
    void getAllParticipants() ;
    void viewParticipantTableWidget() ;
    void viewAddEditParticipant() ;
    QString generateRandomParticipantID() ;
    void deleteParticipant() ;

    /*
     * Widget - Questionnaires View
     */
    QWidget *widget_Questionnaires_View ;
    QVBoxLayout *layout_Vertical_Questionnaires_View ;
    QHBoxLayout *layout_Horizontal_Questionnaires_View ;
    QTableWidget *tableWidget_Questionnaires_View ;
    QPushButton *pushButton_Questionnaires_View_Add ;
    QPushButton *pushButton_Questionnaires_View_Edit ;
    QPushButton *pushButton_Questionnaires_View_Delete ;

    /*
     * Widget - Questionnaires Add/Edit
     */
    QWidget *widget_Questionnaires_AddEdit ;
    QVBoxLayout *layout_Vertical_Questionnaires_AddEdit ;
    QHBoxLayout *layout_Horizontal_Questionnaires_AddEdit_Title ;
    QHBoxLayout *layout_Horizontal_Questionnaires_AddEdit_Note ;
    QVBoxLayout *layout_Vertical_Questionnaires_AddEdit_Questions ;
    QVBoxLayout *layout_Vertical_Questionnaires_AddEdit_New_Question ;
    QHBoxLayout *layout_Horizontal_Questionnaires_AddEdit_New_Question_Title ;
    QHBoxLayout *layout_Horizontal_Questionnaires_AddEdit_New_Question_Range ;
    QHBoxLayout *layout_Horizontal_Questionnaires_AddEdit_AddLine ;
    QLabel *label_Questionnaires_AddEdit_Title ;
    QLabel *label_Questionnaires_AddEdit_Title_ID ;
    QLabel *label_Questionnaires_AddEdit_Note_Title ;
    QLineEdit *lineEdit_Questionnaires_AddEdit_Note ;
    QPushButton *pushButton_Questionnaires_AddEdit_AddLine ;
    QPushButton *pushButton_Questionnaires_AddEdit_Submit ;
    QLabel *label_Questionnaires_AddEdit_Question ;
    QLineEdit *lineEdit_Questionnaires_AddEdit_Question ;
    QComboBox *comboBox_Questionnaires_AddEdit_New_Question_Question_Type ;
    QLabel *label_Questionnaires_AddEdit_Question_Range_Base ;
    QLineEdit *lineEdit_Questionnaires_AddEdit_Question_Range_Base ;
    QLabel *label_Questionnaires_AddEdit_Question_Range_Range ;
    QLineEdit *lineEdit_Questionnaires_AddEdit_Question_Range_Range ;
    QVector<QPushButton *> pushButton_Questionnaires_Remove_Buttons ;
    QVector<QLabel *> label_Questionnaires_Questions ;
    QVector<QWidget *> widget_Questionnaires_Questions ;
    Questionnaire questionnaireAddEdit ;
    QSignalMapper *signalMapperQuestionnaireAddEdit ;

    /*
     * Functions - Questionnaires
     */
    void updateQuestionnaireTableWidget() ;
    void getAllQuestionnaires() ;
    void viewQuestionnaireTableWidget() ;
    void viewAddEditQuestionnaire() ;
    QString generateRandomQuestionnaireID() ;
    QString generateRandomQuestionID(QString type) ;
    void deleteQuestionnaire() ;
    void addNewQuestionToAddEditViewList(Question *question) ;
    void addQuestionToAddEditViewList(Question *question) ;
    void showQuestionInAddEditViewList(QString labelTitle, Question *question) ;
    void removeQuestionFromAddEditViewList(QString title) ;
    void clearQuestionsFromAddEditViewList() ;

    /*
     * Main & Sub Menu Buttons
     */
    //Tertiary
    //Questionnaires
    QVector<QPushButton *> pushButton_Menu_Tertiary_Buttons_Questionnaires ;
    QPushButton *pushButton_Menu_Tertiary_Button_Questionnaire_View ;
    QPushButton *pushButton_Menu_Tertiary_Button_Questionnaire_Add ;
    QPushButton *pushButton_Menu_Tertiary_Button_Questionnaire_Edit ;
    QPushButton *pushButton_Menu_Tertiary_Button_Questionnaire_Remove ;
    void showMenuTertiaryButtonsQuestionnaires() ;

    //Questions
    QVector<QPushButton *> pushButton_Menu_Tertiary_Buttons_Questions ;
    QPushButton *pushButton_Menu_Tertiary_Button_Questions_View ;
    void showMenuTertiaryButtonsQuestions() ;

    //Participants
    QVector<QPushButton *> pushButton_Menu_Tertiary_Buttons_Participants ;
    QPushButton *pushButton_Menu_Tertiary_Button_Participants_View ;
    QPushButton *pushButton_Menu_Tertiary_Button_Participants_Add ;
    QPushButton *pushButton_Menu_Tertiary_Button_Participants_Edit ;
    QPushButton *pushButton_Menu_Tertiary_Button_Participants_Remove ;
    void showMenuTertiaryButtonsParticipants() ;

    //APL
    QVector<QPushButton *> pushButton_Menu_Tertiary_Buttons_Settings_APLs ;
    QPushButton *pushButton_Menu_Tertiary_Button_APL_View ;
    QPushButton *pushButton_Menu_Tertiary_Button_APL_Add ;
    QPushButton *pushButton_Menu_Tertiary_Button_APL_Edit ;
    QPushButton *pushButton_Menu_Tertiary_Button_APL_Remove ;
    void showMenuTertiaryButtonsAPLs() ;

    //User
    QVector<QPushButton *> pushButton_Menu_Tertiary_Buttons_Settings_Users ;
    QPushButton *pushButton_Menu_Tertiary_Button_User_View ;
    QPushButton *pushButton_Menu_Tertiary_Button_User_Add ;
    QPushButton *pushButton_Menu_Tertiary_Button_User_Edit ;
    QPushButton *pushButton_Menu_Tertiary_Button_User_Remove ;

    void initButtons_TertiaryButtons() ;    
    void hideTertiaryMenuButtons() ;

    //Secondary
    //Questionnaires
    QVector<QPushButton *> pushButton_Menu_Secondary_Buttons_Questionnaires ;
    QPushButton *pushButton_Menu_Secondary_Button_Questionnaires ;
    QPushButton *pushButton_Menu_Secondary_Button_Questions ;
    void showMenuSecondaryButtonsQuestionnaires() ;

    //Participants
    QVector<QPushButton *> pushButton_Menu_Secondary_Buttons_Participants ;
    QPushButton *pushButton_Menu_Secondary_Button_Participants ;
    void showMenuSecondaryButtonsParticipants() ;

    //Settings
    QVector<QPushButton *> pushButton_Menu_Secondary_Buttons_Settings ;
    QPushButton *pushButton_Menu_Secondary_Buttons_Settings_APLs ;
    QPushButton *pushButton_Menu_Secondary_Buttons_Settings_Users ;
    void showMenuSecondaryButtonsSettings() ;

    void initButtons_SecondaryButtons() ;
    void hideSecondaryMenuButtons() ;

    //Primary
    QVector<QPushButton *> pushButton_Menu_Primary_Buttons ;
    QPushButton *pushButton_Menu_Primary_Button_Home ;
    QPushButton *pushButton_Menu_Primary_Button_Research ;
    QPushButton *pushButton_Menu_Primary_Button_Questionnaires ;
    QPushButton *pushButton_Menu_Primary_Button_Participants ;
    QPushButton *pushButton_Menu_Primary_Button_Settings ;
    QPushButton *pushButton_Menu_Primary_Button_Collaborate_BackUp ;
    QPushButton *pushButton_Menu_Primary_Button_Lock ;
    QPushButton *pushButton_Menu_Primary_Button_Logout ;
    void initButtons_PrimaryButtons() ;

    /*
     * Resize Event Capture (Overridden from Parent)
     */
    void resizeEvent ( QResizeEvent * event ) ;

    /*
     * Stylesheets
     */
    QString getPrimaryButtonStyleSheet() ;
    QString getSecondaryButtonStyleSheet() ;
    QString getTertiaryButtonStyleSheet() ;
    QString getStyleSheetForLockFrame() ;
    QString getStyleSheetForLoginScreen() ;

private slots:
    void pushButton_Login_Login_clicked() ;

    void pushButton_Menu_Primary_Button_Home_clicked() ;

    void pushButton_Menu_Primary_Button_Settings_clicked() ;

    void pushButton_Menu_Secondary_Buttons_Settings_APLs_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_APLs_View_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_APLs_Add_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_APLs_Edit_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_APLs_Delete_clicked() ;
    void pushButton_APLs_View_Add_clicked() ;
    void pushButton_APLs_View_Edit_clicked() ;
    void pushButton_APLs_View_Delete_clicked() ;
    void tableWidget_ALPs_View_Cell_clicked(const QModelIndex &index) ;
    void pushButton_APLs_AddEdit_Submit_clicked() ;

    void pushButton_Menu_Secondary_Buttons_Settings_Users_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_Users_View_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_Users_Add_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_Users_Edit_clicked() ;
    void pushButton_Menu_Tertiary_Buttons_Settings_Users_Delete_clicked() ;
    void pushButton_Users_View_Add_clicked() ;
    void pushButton_Users_View_Edit_clicked() ;
    void pushButton_Users_View_Delete_clicked() ;
    void tableWidget_Users_View_Cell_clicked(const QModelIndex &index) ;
    void pushButton_Users_AddEdit_Submit_clicked() ;

    void pushButton_Menu_Primary_Button_Participants_clicked() ;

    void pushButton_Menu_Secondary_Button_Participants_clicked() ;
    void pushButton_Menu_Tertiary_Button_Participants_View_clicked() ;
    void pushButton_Menu_Tertiary_Button_Participants_Add_clicked() ;
    void pushButton_Menu_Tertiary_Button_Participants_Edit_clicked() ;
    void pushButton_Menu_Tertiary_Button_Participants_Remove_clicked() ;
    void pushButton_Participants_View_Add_clicked() ;
    void pushButton_Participants_View_Edit_clicked() ;
    void pushButton_Participants_View_Delete_clicked() ;
    void tableWidget_Participants_View_Cell_clicked(const QModelIndex &index) ;
    void pushButton_Participants_AddEdit_Submit_clicked() ;

    void pushButton_Menu_Primary_Button_Questionnaires_clicked() ;

    void pushButton_Menu_Secondary_Button_Questionnaires_clicked() ;
    void pushButton_Menu_Tertiary_Button_Questionnaire_View_clicked() ;
    void pushButton_Menu_Tertiary_Button_Questionnaire_Add_clicked() ;
    void pushButton_Menu_Tertiary_Button_Questionnaire_Edit_clicked() ;
    void pushButton_Menu_Tertiary_Button_Questionnaire_Remove_clicked() ;
    void pushButton_Menu_Tertiary_Button_Questions_View_clicked() ;
    void pushButton_Questionnaires_View_Add_clicked() ;
    void pushButton_Questionnaires_View_Edit_clicked() ;
    void pushButton_Questionnaires_View_Delete_clicked() ;
    void tableWidget_Questionnaires_View_Cell_clicked(const QModelIndex &index) ;
    void pushButton_Questionnaires_AddEdit_Submit_clicked() ;
    void pushButton_Questionnaires_AddEdit_AddLine_clicked() ;
    void comboBox_Questionnaires_AddEdit_New_Question_Question_Type_clicked(QString title) ;
    void pushButton_Questionnaires_AddEdit_Remove_Question_clicked(QString title) ;

    void pushButton_Menu_Secondary_Button_Questions_clicked() ;

    void pushButton_Menu_Primary_Button_Lock_clicked() ;

    void pushButton_Menu_Primary_Button_Logout_clicked() ;
};

#endif // VIEWMAINSCREEN_H
