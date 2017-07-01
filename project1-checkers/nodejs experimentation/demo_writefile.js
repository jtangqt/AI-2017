var fs = require('fs');

fs.appendFile('mynewfile1.txt', 'Hello Content!', function(err){
	if (err) throw err;
	console.log('Saved!'); //the appendfile method appends specific content to a file. If the file does not exist, the file will be created
});