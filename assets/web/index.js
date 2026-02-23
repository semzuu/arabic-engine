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

document.addEventListener('DOMContentLoaded', async () => {
	const hist = document.getElementById('historyList');
	if (!hist) return;

	const roots = await getRoots();
	renderHistory(roots);
})

function renderHistory(data) {
	const list = document.getElementById('historyList');

	if (!data || data.length === 0) {
		list.innerHTML = '<div class="no-data">لا توجد سجلات متاحة حالياً</div>';
		return;
	}

	list.innerHTML = '';

	data.forEach(item => {
		const card = document.createElement('div');
		card.className = 'history-card';

		const derivHTML = item.derivatives.map(w => `<span class="word-tag">${w}</span>`).join('');

		card.innerHTML = `
								<span class="root-label">الجذر</span>
								<span class="root-val">${item.root}</span>
								<div class="words-wrapper">
										${derivHTML}
								</div>
						`;
		list.appendChild(card);
	});
}
