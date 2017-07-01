var fs = require('fs');

fs.open('mynewfile2.txt', 'w', function(err, file){
	if (err) throw err;
	console.log('Saved!'); 
	// open method takes a "flag" as a second argument, if the flag is 'w' for 'writing', the specified file is open for writing
	//if the file does not exist, an empty file is created
});