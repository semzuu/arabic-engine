async function handleValidation() {
	const root = document.getElementById('rootInput').value.trim();
	const word = document.getElementById('wordInput').value.trim();
	const resultDiv = document.getElementById('result-container');

	if (!root || !word) {
		alert("يرجى إدخال الجذر والكلمة معاً");
		return;
	}

	const isValid = await validateWordFromRoot(root, word); 

	resultDiv.style.display = 'block';
	if (isValid) {
		resultDiv.className = 'valid';
		resultDiv.innerText = 'صحيح ✓';
	} else {
		resultDiv.className = 'invalid';
		resultDiv.innerText = 'غير صحيح ✗';
	}
}
