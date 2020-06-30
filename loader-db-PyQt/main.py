# -*- coding: utf-8 -*-
import sys
from PyQt4 import QtCore, QtGui
from SqlConnect import SqlConnect

class SettingsWindow(QtGui.QWidget):
    def __init__(self, parent=None):
        super(SettingsWindow, self).__init__(parent)

        self.setWindowFlags(QtCore.Qt.Dialog | QtCore.Qt.WindowSystemMenuHint)
        self.setWindowModality(QtCore.Qt.WindowModal)
        self.setWindowTitle("SettingsWindow")

        self.host_label = QtGui.QLabel('Host')
        self.host_edit = QtGui.QLineEdit()
        self.host_edit.setText("localhost")

        self.user_label = QtGui.QLabel('User')
        self.user_edit = QtGui.QLineEdit()
        self.user_edit.setText("root")

        self.password_label = QtGui.QLabel('Password')
        self.password_edit = QtGui.QLineEdit()
        self.password_edit.setText("11")

        self.db_label = QtGui.QLabel('DB name')
        self.db_edit = QtGui.QLineEdit()
        self.db_edit.setText("test")

        self.butt_hide = QtGui.QPushButton('Save')
        self.butt_hide.clicked.connect(self.button_click)

        grid = QtGui.QGridLayout()
        grid.addWidget(self.host_label, 1, 0)
        grid.addWidget(self.host_edit, 1, 1)
        grid.addWidget(self.user_label, 2, 0)
        grid.addWidget(self.user_edit, 2, 1)
        grid.addWidget(self.password_label, 3, 0)
        grid.addWidget(self.password_edit, 3, 1)
        grid.addWidget(self.db_label, 4, 0)
        grid.addWidget(self.db_edit, 4, 1)
        grid.addWidget(self.butt_hide)

        self.setLayout(grid)
        self.resize(350, 100)

    def button_click(self):
        SqlConnect.set_parametr(self,
                                self.host_edit.text(),
                                self.user_edit.text(),
                                self.password_edit.text(),
                                self.db_edit.text()
                                )


class MainWindow(QtGui.QWidget):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)

        self.model = QtGui.QStandardItemModel()

        self.proxy = QtGui.QSortFilterProxyModel()
        self.proxy.setSourceModel(self.model)
        self.proxy.setFilterKeyColumn(-1)

        self.view = QtGui.QTreeView()
        self.view.setAlternatingRowColors(True)
        self.view.setModel(self.proxy)

        self.btn_show_settings = QtGui.QPushButton('SettingsWindow')
        self.btn_load_table = QtGui.QPushButton('LoadTable')

        self.filter_syntax_comboBox = QtGui.QComboBox()
        self.filter_syntax_comboBox.addItem("Regular expression")
        self.filter_syntax_comboBox.addItem("Wildcard")
        self.filter_syntax_comboBox.addItem("Fixed string")

        self.filter_column_comboBox = QtGui.QComboBox()
        self.filter_column_comboBox.addItem("All")
        self.headers = ["Name", "DoB / Age", "Sex", "Snils", "Serial / Number"]
        for i in self.headers:
            self.filter_column_comboBox.addItem(i)

        self.line_edit = QtGui.QLineEdit()

        grid = QtGui.QGridLayout()
        grid.addWidget(self.btn_show_settings,  0, 0, 1, 1)
        grid.addWidget(self.btn_load_table, 1, 0, 1, 1)
        grid.addWidget(self.filter_syntax_comboBox, 0, 2)
        grid.addWidget(self.filter_column_comboBox, 1, 2)
        grid.addWidget(self.line_edit, 3, 0, 1, 3)
        grid.addWidget(self.view, 4, 0, 1, 3)

        self.btn_load_table.clicked.connect(self.load_table)
        self.btn_show_settings.clicked.connect(self.show_settings)
        self.line_edit.textChanged.connect(self.on_lineEdit_textChanged)
        self.filter_syntax_comboBox.currentIndexChanged.connect(self.filterRegExpChanged)
        self.filter_syntax = QtCore.QRegExp.RegExp
        self.filter_column_comboBox.currentIndexChanged.connect(self.on_comboBox_currentIndexChanged)

        self.setLayout(grid)
        self.setWindowTitle("MainWindow")
        self.resize(700, 400)

    def show_settings(self):
        win = SettingsWindow(self)
        win.show()

    @QtCore.pyqtSlot(int)
    def filterRegExpChanged(self, index):
        if index == 0:
            self.filter_syntax = QtCore.QRegExp.RegExp
        elif index == 1:
            self.filter_syntax = QtCore.QRegExp.Wildcard
        elif index == 2:
            self.filter_syntax = QtCore.QRegExp.FixedString

    @QtCore.pyqtSlot(int)
    def on_comboBox_currentIndexChanged(self, index):
        if index == 0:
            self.proxy.setFilterKeyColumn(-1)
        else:
            self.proxy.setFilterKeyColumn(index-1)

    @QtCore.pyqtSlot(str)
    def on_lineEdit_textChanged(self, text):
        search = QtCore.QRegExp(text,
                                QtCore.Qt.CaseInsensitive,
                                self.filter_syntax
                                )
        self.proxy.setFilterRegExp(search)

    def load_table(self):
        self.model.clear()

        q = SqlConnect()
        q.connectDB(self)

        fio_query = q.exec_query("SELECT firstName, patrName, lastName  FROM test.Client  order by id;")
        dob_query = q.exec_query("SELECT birthDate, TIMESTAMPDIFF(YEAR, birthDate, curdate()) AS years FROM test.Client  order by id; ")
        sex_query = q.exec_query('SELECT CASE WHEN sex = 1 THEN "M" ELSE "W" END FROM Client  order by id;')
        snils_query = q.exec_query('SELECT snils FROM test.Client order by id;')
        document_query = q.exec_query('SELECT  client_id, serial, number FROM test.Client c LEFT JOIN test.ClientDocument d ON c.id=d.client_id ORDER BY client_id;')

        incriment_column = 0
        fio_size = fio_query.size()
        list_column = [list() for i in range(fio_size)]

        while fio_query.next():
            FIO = ""
            for j in range(0, 3):
                FIO = FIO + fio_query.value(j).toString() + " "
            list_column[incriment_column].append(QtGui.QStandardItem(FIO))
        incriment_column += 1

        while dob_query.next():
            DOB = dob_query.value(0).toString() + ' / ' + dob_query.value(1).toString()
            list_column[incriment_column].append(QtGui.QStandardItem(DOB))
        incriment_column += 1

        while sex_query.next():
            sex_string = sex_query.value(0).toString()
            list_column[incriment_column].append(QtGui.QStandardItem(sex_string))
        incriment_column += 1

        while snils_query.next():
            snils_string = snils_query.value(0).toString()
            list_column[incriment_column].append(QtGui.QStandardItem(snils_string))
        incriment_column += 1

        client_id = ""
        while document_query.next():
            if client_id == document_query.value(0).toString():
                QtGui.QMessageBox.critical(self,
                                           QtGui.qApp.tr("Duplicate row found"),
                                           QtGui.qApp.tr("Row client_id = {} is dublicated.\nClick Cancel to exit.".format(client_id)),
                                           QtGui.QMessageBox.Cancel)
                continue

            client_id = document_query.value(0).toString()
            serial_numder = document_query.value(1).toString() + " / " + document_query.value(2).toString()
            list_column[incriment_column].append(QtGui.QStandardItem(serial_numder))

        for i in range(0, fio_size):
            self.model.invisibleRootItem().appendRow([ list_column[0][i],
                                                       list_column[1][i],
                                                       list_column[2][i],
                                                       list_column[3][i],
                                                       list_column[4][i]
                                                       ])

        for i in range(len(self.headers)):
            self.view.resizeColumnToContents(i)
            self.model.setHeaderData(i, QtCore.Qt.Horizontal, self.headers[i])


if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())