
//Event list read from file is processed here to arrange coordinates as necessary
function processCoordinates(eventList){
	
	var startTime=eventList[0][1];
	var end=eventList[eventList.length-1]-startTime;
	var verticalpadding=0;
	
	
	eventList.push([1,480,100,0,"line"]);
	for (i = 0; i < eventList.length; i++) {
		switch(eventList[i][0]) {
    		case 0:
        		break;
    		case 1:
        		verticalpadding=100;
        		break;
        	case 2:
        		verticalpadding=200;
        		break;
        	case 3:
        		verticalpadding=300;
        		break;
		}
		eventList[i][1]-=startTime;
		eventList[i][1]+=horizontalpadding;
		eventList[i][2]+=verticalpadding;
		var lineEvent=[];
	}

	return eventList;

}