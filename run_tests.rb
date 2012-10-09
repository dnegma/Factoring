test = Array.new
input = ""

IO.popen("./pollard_run", mode="w+"){|p_io|

	# print arr ,"\n"
	File.foreach("test_cases.input") { |line|
		p_io.write(line)
		print line
		while input != "\n" do
			input = p_io.readline
			print input
		end
		
		input = ""
	}
}
