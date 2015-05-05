function loadEvent(fn) {						//Funktion so gör det möjligt att ladda flera funktioner när sidan laddas.
	var oldonload = window.onload;
	if (typeof window.onload != 'function') {
		window.onload = fn;
	}
	else {
		window.onload = function() {
			oldonload();
			fn();
		}
	}
}

var regEvent=(function(){						//Funktion som gör att man kan ska event som funkar i både IE och moderna webbläsare utan något extra arbete.
	var elem=document.createElement('div');
	if(elem.addEventListener){
		return function(elem, eventName, fn){
			elem.addEventListener(eventName, fn, false);
		}
	}
	else if(elem.attachEvent){
		return function(elem, eventName, fn){
			elem.attachEvent('on'+eventName, fn);
		}
	}
})();

function addEvent(elem, eventName, fn){			//Funktion man använder för att lägga till nya event så det automatiskt funker i IE också.
	var cb=(function(){
		return function(event){
			fn.call(this, normaliseEvent(event || window.event));
		}
	})();
	regEvent(elem, eventName, cb);
}

function normaliseEvent(event) {				//Funktion som normaliserar events.
	if (!event.stopPropagation) {
		event.stopPropagation = function() {this.cancelBubble = true;};
		event.preventDefault = function() {this.returnValue = false;};
	}
	if (!event.stop) {
		event.stop = function() {
			this.stopPropagation();
			this.preventDefault();
		};
	}
	if (event.srcElement && !event.target) {
			event.target = event.srcElement;
	}
	return event;
}

loadEvent(function(){							//Alla funktioner innanför här laddas in samtidigt som sidan.
	
	var steps = [];
	var open = false;

	function addStep(hops, time){				//Funktion som lägger till mäsksteg i arrayen och i listan.
		steps.push([hops,time]);
		updateSteps();
	}

	function updateSteps(){						//Funktion som skriver ut alla steg som finns i arrayen i en lista med ett kryss efter..
		document.getElementById('steps').innerHTML = "";
		for(var i = 0; i < steps.length; i++){
			var newParagraph = document.createElement('p');
			newParagraph.textContent = "Steg " + (i+1) + " " + steps[i][0] + "  Läggs i " + steps[i][1] + " min innan slut";
			var spanDelete = document.createElement("span");
		    spanDelete.id = i;
		    spanDelete.className = "delete";
		    spanDelete.innerHTML = "&nbsp;&#10007;&nbsp;";
		    spanDelete.onclick = function(){
		    	deleteStep(this.id);
		    }
		    newParagraph.appendChild(spanDelete);
			document.getElementById('steps').appendChild(newParagraph);
		}
	}

	function deleteStep(id){					//Funktion som tar bort ett värde i arrayen och sedan kallar på en funktion som skriver ut arrayen igen.
		steps.splice(id,1);
		updateSteps();
	}

	function validateTotalTime(totalTime){				//Funktion som kollar så tiden är en siffra över 0.
		if(totalTime.value != ""){
			if(/^\d+$/.test(totalTime.value) && totalTime.value > 0){
				totalTime.style.backgroundColor = "white";
				return true;
			}
			else{
				totalTime.focus();
				totalTime.style.backgroundColor = "#FF4D4D";
				return false;
			}
		}
		else{
			totalTime.focus();
			totalTime.style.backgroundColor = "#FF4D4D";
			return false;
		}
	}

	function validateHops(hops){				//Funktion som kollar så temperaturen är en siffra mellan 0 och 100.
		hops.setCustomValidity("");
		if(hops.value != "" && /^[a-zA-ZåäöÅÄÖ0-9]+$/.test(hops.value)){
			hops.style.backgroundColor = "white";
			return true;
		}
		else{
			hops.focus();
			hops.setCustomValidity("Inga mellanslag");
			hops.style.backgroundColor = "#FF4D4D";
			return false;
		}
	}
	
	function validateTime(time){				//Funktion som kollar så tiden är en siffra över 0.
		if(time.value != ""){
			if(/^\d+$/.test(time.value) && time.value > 0 && parseInt(time.value) <= parseInt(document.getElementById('boilTime').value)){
				time.style.backgroundColor = "white";
				return true;
			}
			else{
				time.focus();
				time.style.backgroundColor = "#FF4D4D";
				return false;
			}
		}
		else{
			time.focus();
			time.style.backgroundColor = "#FF4D4D";
			return false;
		}
	}

	addEvent(document.getElementById('boilTime'), 'keypress', function(e){		//Event som skickar användaren vidare till time-fältet
		if(e.keyCode == 13){												//när man är i temp-fältet och trycker Enter.
			document.getElementById('hops').focus();
		}
	});

	addEvent(document.getElementById('hops'), 'keypress', function(e){		//Event som skickar användaren vidare till time-fältet
		if(e.keyCode == 13){												//när man är i temp-fältet och trycker Enter.
			e.preventDefault();
			document.getElementById('time').focus();
		}
	});

	addEvent(document.getElementById('newStep'),'submit',function(e){	//Event som lyssnar på submitknappen och gör alla checkar för att sedan
		e.preventDefault();
		if (validateTotalTime(document.getElementById('boilTime'))){
			if(validateHops(document.getElementById('hops'))){				//lägga till steget i listan.
				if(validateTime(document.getElementById('time'))){
					addStep(document.getElementById('hops').value, document.getElementById('time').value);
					document.getElementById('hops').value = "";
					document.getElementById('hops').focus();
					document.getElementById('time').value = "";
				}
			}
		}
	});



	addEvent(document.getElementById('mainMenu'), 'click', function(e){
		window.location.href = "index.html";
	});
});