from ui_cliente import *
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import sys, socket

#class Cliente(PyQt4.QtGui.QDialog, Ui_Dialog):
class Cliente(QDialog, Ui_Dialog):

	def __init__(self, parent=None):
		super(Cliente, self).__init__(parent)
		self.setupUi(self)
		self.psEnviar.clicked.connect(self.clicked)

		self.txtTipoMedida.setText("0")
		self.txtPosicaoMotor.setText("25")
		self.txtCorrenteLED.setText("20")
		self.txtAltaTensao.setText("0")
		self.txtSinal.setText("0")
		self.txtNumeroAmostras.setText("5")

		HOST = 'localhost'
		PORT = 2534
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		mandar = (HOST, PORT)
		self.s.connect(mandar)
		self.counter = 0
	def clicked(self):
		tipoMedida = int(str(self.txtTipoMedida.text()))
		posicaoMotor = int(str(self.txtPosicaoMotor.text()))
		correnteLED = int(str(self.txtCorrenteLED.text()))
		altaTensao = int(str(self.txtAltaTensao.text()))
		sinal = int(str(self.txtSinal.text()))
		numeroAmostras = int(str(self.txtNumeroAmostras.text()))
		pacote = [self.counter, tipoMedida, posicaoMotor, correnteLED, altaTensao, sinal, numeroAmostras, 70, 73]
		hexdata = ''.join([chr(item) for item in pacote])
		self.s.send(hexdata)
		print "Mensagem enviada!"
		self.counter = self.counter + 1

		for i in range(1):
			recebido = self.s.recv(1024)
			#print repr(recebido[0])

app = QApplication(sys.argv)
c = Cliente()
c.exec_()
	
