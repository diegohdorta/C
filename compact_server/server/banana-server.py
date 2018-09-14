from asyncio import *
from functools import wraps
import signal

loop = get_event_loop()
save_handler = loop.call_soon(lambda: None)

def kill_on_error(f):
	@wraps(f)
	def g(*args, **kwargs):
		print(" Running Banana Server 2014...\n")
		print(" Ctrl + C to cancel\n")
		try:
			v = yield from f(*args, **kwargs)
			return v
		except Exception as e:
			print(e)
			loop.stop()
	return g

def on_interrupt():
	print('interrupted')
	for task in Task.all_tasks():
		task.cancel()
#	if not done.done():
#		done.set_result(1)
	loop.stop()

def save(store):
	print('Saving: ', store)


def print_message(writer):

	writer.write(b"\033[2J")
	writer.write(b"//\						|            ..:: Banana Server 2014 ::..		\n")
	writer.write(b"V  \						|  							\n")
	writer.write(b" \  \						|        You can read, write, delete messages!		\n")
	writer.write(b"  \,'.`-.					|  Talk to Banana Server typing messages on terminal	\n")
	writer.write(b"   |\ `. `.					|							\n")
	writer.write(b"   ( \  `. `-.                        _,.-:\	| 							\n")
	writer.write(b"    \ \   `.  `-._             __..--' ,-';/	|	       Use: get, put, or delete.		\n")
	writer.write(b"     \ `.   `-.   `-..___..---'   _.--' ,'/	|							\n")
	writer.write(b"      `. `.    `-._        __..--'    ,' /	|							\n")
	writer.write(b"        `. `-_     ``--..''       _.-' ,'	|							\n")
	writer.write(b"          `-_ `-.___        __,--'   ,'		|							\n")
	writer.write(b"             `-.__  `----\"\"\"    __,'\"        	|  	We can go all night! Version 1.0.0	\n")
	writer.write(b"                  `--..____..--'		|							\n")


@coroutine
def process(command, reader, writer, store):
	global save_handler
	message = command
	command = command.split()


	if len(command) == 0:
		writer.write(b'Hello, banana eater!\n')

		return

	op = command[0]
	if op == b'get':
		try:
			writer.write(store[command[1]] + b'\n')
		except KeyError:
			writer.write(b'key-error\n')
		except IndexError:
			writer.write(b'op-error\n')
	elif op == b'put':
		try:
			store[command[1]] = command[2]
			writer.write(command[2] + b'\n')
			save_handler.cancel()
			save_handler = loop.call_later(2, save, store)
		except IndexError:
			writer.write(b'op-error\n')
	elif op == b'delete':
		try:
			v = store[command[1]]
			del store[command[1]]
			writer.write(v + b'\n')
		except KeyError:
			writer.write(b'key-error\n')
# .strip() is used to remove the final caracters
# encode converts normal string in binary
	elif (message.strip() == b'who are you?'):
		writer.write(b'I\'m Banana Server 2014! :)\n')

	elif (message.strip() == b'how old are you?'):
		writer.write(b'I\'m in my first version yet, I\'m brand new! :)\n')

	elif (message.strip() == b'you are a bitch'):
		writer.write(b'Go fuck yourself! By!\n')
		loop.close()

	elif (message.strip() == b'who am i?'):
		#ip = writer.getpeername()
		address = writer.get_extra_info('peername')
		print ("ip = ",address[0],address[1])
		ip = address[0]
		port = address[1]
		writer.write(('\033[32myou are ip/port: %s : %s\033[0m\n' % (ip, port)).encode() )

	else:
		writer.write(b'Sorry... I did not understand, say it again?\n')

@coroutine
@kill_on_error
def on_connection(reader, writer):

	print_message(writer)
	try:
		store = {}
		while True:
			data = yield from reader.readline()
			if len(data) == 0: return
			yield from process(data, reader, writer, store)
	except CancelledError as e:
		pass
	finally:
		try:
			yield from writer.drain()
		except Exception as e:
			print('write error:', e)
		try:
			writer.close()
		except Exception as e:
			print('close error:', e)

def main():
	loop.add_signal_handler(signal.SIGINT, on_interrupt)
	loop.add_signal_handler(signal.SIGTERM, on_interrupt)
	loop.add_signal_handler(signal.SIGQUIT, on_interrupt)
	server = loop.run_until_complete(start_server(on_connection, '', 12345))
	loop.run_forever()
	server.close()
	loop.run_until_complete(server.wait_closed())
	loop.close()
	print('finished.')

if __name__ == '__main__': main()

