
//Event list read from file is processed here to arrange coordinates as necessary
function processCoordinates(eventList){
	
	var startTime=eventList[0][1];
	var end=eventList[eventList.length-1]-startTime;
	var verticalpadding=0;
	

	//eventList.push([1,480,100,0,"line"]);
	for (i = 0; i < eventList.length; i++) {
		switch(eventList[i][0]) {
    		case 0:
    			verticalpadding=100;
        		break;
    		case 1:
        		verticalpadding=200;
        		break;
        	case 2:
        		verticalpadding=300;
        		break;
        	case 3:
        		verticalpadding=400;
        		break;
		}
		eventList[i][1]-=startTime;
		eventList[i][1]+=horizontalpadding;
		eventList[i][2]+=verticalpadding;
		var lineEvent=[];
	}

	return eventList;

}

//inputlist element [cpu,start,end,duration,hex,name]
//eventlist element [cpu,x,y,duration,hex,name]
function generateCoordinates(inputlist){
	var eventlist=[];
	for (i = 0; i < inputlist.length; i++) {
		inputlist[i][1]=(inputlist[i][1]/100)*hundredNanotoPixel;
		inputlist[i][2]=0;	
		inputlist[i][3]=(inputlist[i][1]/100)*hundredNanotoPixel;
	}
	return inputlist;
}