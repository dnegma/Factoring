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
			if input.eql? "fail\n"
				i+=1
			end
			print input
		end
		
		input = ""
	}

	print "failed ", i , " tests off ",j ," cases\n"
}
