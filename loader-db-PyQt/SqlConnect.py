from PyQt4 import QtGui
from PyQt4.QtSql import QSqlDatabase, QSqlQuery


class SqlConnect():
    host = "localhost"
    user = "root"
    password = "11"
    db_name = "test"

    def __init__(self):
        self.db = QSqlDatabase.addDatabase("QMYSQL");


    @staticmethod
    def set_parametr(parent, *args):
        args = list(args)

        try:
            for i in range(len(args)):
                args[i] = str(args[i])
                args[i] = "".join(args[i].split())
        except:
            QtGui.QMessageBox.critical(parent,
                                       QtGui.qApp.tr("English please"),
                                       QtGui.qApp.tr("English please"),
                                       QtGui.QMessageBox.Escape)
        else:
            SqlConnect.host = args[0]
            SqlConnect.user = args[1]
            SqlConnect.password = args[2]
            SqlConnect.db_name = args[3]


    def connectDB(self, parent=None):
        self.db.setHostName(self.host)
        self.db.setDatabaseName(self.db_name)
        self.db.setUserName(self.user)
        self.db.setPassword(self.password)

        if not self.db.open():
            QtGui.QMessageBox.critical(parent,
                                       QtGui.qApp.tr("Cannot open database"),
                                       QtGui.qApp.tr("Cannot open database. \nMaybe you set incorrect settings."),
                                       QtGui.QMessageBox.Cancel)


    def exec_query(self, q_string):
        query = QSqlQuery(self.db)
        query.exec_(q_string)
        return query

