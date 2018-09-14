#!/usr/bin/env julia

function process(command, client, store)
	try
		if length(command) == 0 || command[1] == "hi"
			write(client, "hello\n")
		elseif command[1] == "hello"
			write(client, "hi\n")
		elseif command[1] == "get"
			v = get(store, command[2], "key-error")
			write(client, "$v\n")
		elseif command[1] == "put"
			store[command[2]] = command[3]
			write(client, "$(command[3])\n")
		elseif command[1] == "delete"
			v = pop!(store, command[2], "key-error")
			write(client, "$v\n")
		elseif command[1] == "keys"
			write(client, "$store\n")
		else
			write(client, "huh?\n")
		end
	catch
		write(client, "op-error\n")
	end
		
end

function connection(client, store)
	for data in eachline(client)
		data = rstrip(data)
		process(split(data), client, store)
	end
	
	println("done")
	close(client)
end

function main()
	store = Dict{String, String}()
	server = listen(IPv4(0), 12345)
	while true
		client = accept(server)
		@schedule connection(client, store)
	end
end

main()

