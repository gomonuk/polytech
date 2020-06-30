import sys
#from PyQt4.QtGui import *
from PyQt4.QtGui import QApplication, QTextBrowser
import SqlConnect

app = QApplication(sys.argv)
w = QTextBrowser()

q = SqlConnect.SqlConnect()
q.connectDB()
query = q.exec_query("SELECT firstName, patrName, lastName  FROM test.Client;")


while query.next():
    table = query.value(1).toString()
    w.insertHtml('%s<br />' % table)

w.insertHtml('<br />')
w.insertHtml('TOTAL %s TABLES' % query.size())

w.show()
sys.exit(app.exec_())