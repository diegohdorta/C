--------------------------------------------------------------------------------
LNLS - Brazilian Synchrotron Light Laboratory
--------------------------------------------------------------------------------
Medipix Server - 15/10/1015
--------------------------------------------------------------------------------
Description:
"....".


--------------------------------------------------------------------------------
COMO INSTALAR:
--------------------------------------------------------------------------------

1 - Baixe a versão mais recente do IOC do Medipix e instale no PXI.
2 - Atualize o arquivo medipix.config com os IP e portas corretas.
3 - Inicie uma instância do servidor na VM Medipix com a porta correta.
4 - Inicie o Medipix server epics com a porta correta para recebimento dos comandos.

Cada linha de luz terá uma instância do servidor, no qual o IP será o mesmo, 
mas a porta será diferente:

Iniciando o servidor:
$ ./server_nome_da_linha port

Os arquivos ficaram salvos em suas respectivas áreas de dados:
/storage/nome_da_linha



--------------------------------------------------------------------------------
TABELA
--------------------------------------------------------------------------------
BEAMLINE:	IP_VM:PORTA TCP CONTROLE:	IP_MEDIPIX/PORTA UDP COMANDO:		IP_VM:PORTA UDP PACOTE:

IMX		IP_VM:5000			IP_MEDIPIX:4000				IP_VM:3000
TGM		IP_VM:5100			IP_MEDIPIX:4100				IP_VM:3100
PGM		IP_VM:5200			IP_MEDIPIX:4200				IP_VM:3200
SGM		IP_VM:5300			IP_MEDIPIX:4300				IP_VM:3300
XRF		IP_VM:5400			IP_MEDIPIX:4400				IP_VM:3400
--------------------------------------------------------------------------------
Descrição da Tabela:
--------------------------------------------------------------------------------
IP_VM: 		IP da máquina virtual que roda o servidor.
IP_MEDIPIX: 	IP do Medipix. I

IP_VM:PORTA TCP CONTROLE: 

	Endereço em que o IOC conversará com o servidor para enviar as
informações necessárias para receber os pacotes.

No IOC coloque o mesmo endereço no arquivo medipix.config, na variável de ambiente:

epicsEnvSet("SERVER_IP/PORT_VARIABLE","10.2.101.35:4000")


PORTA UDP COMANDO: 

	Porta em que o IOC se comunicará com o Medipix, o IP e porta
são iniciados de acordo com as configurações do server epics (Franz).


PORTA UDP PACOTE: 

	Porta em que o Medipix enviará os pacotes
--------------------------------------------------------------------------------
HOW TO USE:
--------------------------------------------------------------------------------




