function parseTrace(lines){
	  var entries = {};
    for(var line = 0; line < lines.length; line++){

      	if(!lines[line]){
      		continue;
      	}

      	var words = lines[line].split(',');

      	// console.log(words);
      	if(words.length != 6){
      		console.log("entry length is not 6!, not parsing");
      		return;
      	}

      	var cpu = parseInt(words[0]);
      	var starttime = parseInt(words[1]);
      	var endtime = parseInt(words[2]);
      	var duration = parseInt(words[3]);
      	var type = parseInt(words[4],16);
      	var name = words[5];

      	if(!(cpu in entries)){
      		entries[cpu] = [];
      	}
      	entries[cpu].push([cpu,starttime,endtime,duration,type,name]);
    }
    // console.log(entries[3][0][1]);
    return entries;
}