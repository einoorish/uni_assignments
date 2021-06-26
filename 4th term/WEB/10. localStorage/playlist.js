function init() {
	var button = document.getElementById("addButton");
	button.onclick = handleButtonClick;

	button = document.getElementById("deleteAllButton");
	button.onclick = deleteAllRecords;

	button = document.getElementById("deleteButton");
	button.onclick = deleteRecord;
	loadPlaylist();
}

function handleButtonClick() {
	var textInput = document.getElementById("songTextInput");
	var songName = textInput.value;
	if(songName=="") {
		alert("Будь ласка введіть пісню");
	}

	let q = save(songName);

	if (q) {
		var li = document.createElement("li");
		li.innerHTML = songName; 
		var ul = document.getElementById("playlist");
		ul.appendChild(li);
 	} else {
 		alert("Данний елемент вже знаходиться в списку");
	} 

}

window.onload = init;