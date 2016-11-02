// Draw a width * height rectangle with color at position (x, y).

function colorRGB(colorName) {
	if (colorName == "blue") return "rgb(0,0,255)";
	if (colorName == "red") return "rgb(255,0,0)";
	if (colorName == "green") return "rgb(0,255,0)";
	if (colorName == "black") return "rgb(0,0,0)";
	if (colorName == "white") return "rgb(250,255,255)";
	return "rgb(0,0,0)";
}

function drawRectangle(x, y, width, height, color) {
	return "<rect x=\""+ x +"\" y=\""+ y +"\" width=\"" + width +"\" height=\""
		+ height + "\" style=\"fill:" + colorRGB(color) + ";stroke-width:3\" />"
}
function drawTwoColorRec(x, y, width, height, color1, color2) {
}

