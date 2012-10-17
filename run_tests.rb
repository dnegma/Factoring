WAIT_FOR_INPUT=false
ARGV.each do |a|
	case a
	when "wait", "w"
		WAIT_FOR_INPUT = true
	end
end

test = Array.new
input = ""
i = 0
j=0

IO.popen("./pollard_run", mode="w+"){|p_io|
	
	# print arr ,"\n"
	File.foreach("test_cases.input") { |line|
		j+=1
		p_io.write(line)
		print line
		
		while input != "\n" do
			input = p_io.readline
			if input.match(/^#/)
				# Do nothing
			elsif input.eql? "fail\n"
				i+=1
			end
			print input
		end
		
		if WAIT_FOR_INPUT
			puts "continue(y/n)"
			if 'n' == $stdin.gets.chomp 
				exit 
			end
		end

		input = ""
	}

	print "failed ", i , " tests off ",j ," cases\n"
}
