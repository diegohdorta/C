# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'cliente.ui'
#
# Created: Fri Feb  7 21:04:27 2014
#      by: PyQt4 UI code generator 4.9.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName(_fromUtf8("Dialog"))
        Dialog.resize(620, 180)
        self.txtTipoMedida = QtGui.QLineEdit(Dialog)
        self.txtTipoMedida.setGeometry(QtCore.QRect(30, 90, 61, 21))
        self.txtTipoMedida.setObjectName(_fromUtf8("txtTipoMedida"))
        self.txtPosicaoMotor = QtGui.QLineEdit(Dialog)
        self.txtPosicaoMotor.setGeometry(QtCore.QRect(120, 90, 61, 21))
        self.txtPosicaoMotor.setObjectName(_fromUtf8("txtPosicaoMotor"))
        self.txtCorrenteLED = QtGui.QLineEdit(Dialog)
        self.txtCorrenteLED.setGeometry(QtCore.QRect(220, 90, 61, 21))
        self.txtCorrenteLED.setObjectName(_fromUtf8("txtCorrenteLED"))
        self.txtAltaTensao = QtGui.QLineEdit(Dialog)
        self.txtAltaTensao.setGeometry(QtCore.QRect(330, 90, 61, 21))
        self.txtAltaTensao.setObjectName(_fromUtf8("txtAltaTensao"))
        self.txtSinal = QtGui.QLineEdit(Dialog)
        self.txtSinal.setGeometry(QtCore.QRect(420, 90, 61, 21))
        self.txtSinal.setObjectName(_fromUtf8("txtSinal"))
        self.txtNumeroAmostras = QtGui.QLineEdit(Dialog)
        self.txtNumeroAmostras.setGeometry(QtCore.QRect(500, 90, 61, 21))
        self.txtNumeroAmostras.setObjectName(_fromUtf8("txtNumeroAmostras"))
        self.psEnviar = QtGui.QPushButton(Dialog)
        self.psEnviar.setEnabled(True)
        self.psEnviar.setGeometry(QtCore.QRect(280, 150, 83, 24))
        self.psEnviar.setObjectName(_fromUtf8("psEnviar"))
        self.label = QtGui.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(20, 70, 81, 16))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(120, 70, 101, 16))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(220, 70, 91, 16))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.label_4 = QtGui.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(330, 70, 81, 16))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.label_5 = QtGui.QLabel(Dialog)
        self.label_5.setGeometry(QtCore.QRect(420, 70, 57, 14))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_6 = QtGui.QLabel(Dialog)
        self.label_6.setGeometry(QtCore.QRect(500, 70, 121, 16))
        self.label_6.setObjectName(_fromUtf8("label_6"))

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.psEnviar.setText(QtGui.QApplication.translate("Dialog", "Enviar", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Dialog", "Tipo Medida", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("Dialog", "Posicao Motor", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("Dialog", "Corrente LED", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("Dialog", "Alta Tensao", None, QtGui.QApplication.UnicodeUTF8))
        self.label_5.setText(QtGui.QApplication.translate("Dialog", "Sinal", None, QtGui.QApplication.UnicodeUTF8))
        self.label_6.setText(QtGui.QApplication.translate("Dialog", "Numero Amostras", None, QtGui.QApplication.UnicodeUTF8))

