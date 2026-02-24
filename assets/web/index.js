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

async function addSchemeRow() {
	const container = document.getElementById('schemes-container');
	const newRow = document.createElement('div');
	newRow.className = 'scheme-row';

	const schemes = await getSchemes();
	const schemesHTML = schemes.map((scheme) => `
		<option value="${scheme.name}">${scheme.name}</option>`).join('');
	newRow.innerHTML = `
						<select class="scheme-select">
								<option value="" disabled selected>اختر الوزن...</option>
								${schemesHTML}
						</select>
						<button class="remove-btn" onclick="removeRow(this)">✕</button>
				`;
	container.appendChild(newRow);
}

function removeRow(btn) {
	const rows = document.querySelectorAll('.scheme-row');
	if (rows.length > 1) {
		btn.parentElement.remove();
	} else {
		alert("يجب أن يكون هناك وزن واحد على الأقل");
	}
}

async function generateWords() {
	const root = document.getElementById('rootInput').value.trim();
	const selects = document.querySelectorAll('.scheme-select');
	const resultsList = document.getElementById('results-list');

	// Extract selected values
	const selectedSchemes = Array.from(selects).map(s => s.value).filter(v => v !== "");

	if (!root || selectedSchemes.length === 0) {
		alert("يرجى إدخال الجذر واختيار وزن واحد على الأقل");
		return;
	}

	const results = await Promise.all(selectedSchemes.map(async (scheme) => {
		console.log("scheme", scheme);
		const word = await generateWord(root, scheme);
		return `كلمة '${word}' من وزن '${scheme}' للجذر '${root}'`;
	}))

	// Display Results
	resultsList.innerHTML = '';
	results.forEach(word => {
		const li = document.createElement('div');
		li.className = 'result-item';
		li.innerText = word;
		resultsList.appendChild(li);
	});
}

document.addEventListener('DOMContentLoaded', async () => {
	const list = document.getElementById('schemeListBody');
	if (!list) return;
	await renderSchemes();
})

async function renderSchemes() {
	const tableBody = document.getElementById('schemeListBody');

	tableBody.innerHTML = '';

	const schemesData = await getSchemes();
	if (!schemesData || schemesData.length === 0) {
		tableBody.innerHTML = '<tr><td colspan="3" style="text-align:center; padding:20px; color:#94a3b8;">لا توجد أوزان مضافة حالياً</td></tr>';
		return;
	}

	schemesData.forEach((scheme, index) => {
		const row = document.createElement('tr');
		row.className = 'scheme-item';

		row.innerHTML = `
						<td>${scheme.name}</td>
						<td><span class="pattern-tag">${scheme.pattern}</span></td>
						<td>
								<div class="action-btns">
										<button class="edit-btn"
														onclick="editScheme('${scheme.name}', '${scheme.pattern}')"
														title="تعديل">✎</button>
										<button class="delete-btn"
														onclick="handleDelete('${scheme.name}')"
														title="حذف">✕</button>
								</div>
						</td>
				`;

		tableBody.appendChild(row);
	});
}

// Updated delete handler to work with your data logic
async function handleDelete(name) {
	if (confirm(`هل أنت متأكد من حذف الوزن "${name}"؟`)) {
		await removeScheme(name);
		await renderSchemes();
	}
}

async function saveScheme() {
	const name = document.getElementById('schemeName').value.trim();
	const pattern = document.getElementById('schemePattern').value.trim();

	await addScheme(name, pattern);
	await renderSchemes();
}

function editScheme(name, pattern) {
	document.getElementById('modalName').value = name;
	document.getElementById('modalPattern').value = pattern;
	document.getElementById('patternModal').style.display = 'flex';
}

// Function to close the popup
function closeModal() {
	document.getElementById('patternModal').style.display = 'none';
}

// Function to collect data and trigger your save logic
async function saveModalData() {
	const name = document.getElementById('modalName').value;
	const pattern = document.getElementById('modalPattern').value;

	if (!name || !pattern) {
		alert("يرجى ملء كافة الحقول");
		return;
	}

	await removeScheme(name);
	await addScheme(name, pattern);
	await renderSchemes();
	closeModal();
}

// Close if user clicks the background
window.onclick = function(event) {
	const modal = document.getElementById('patternModal');
	if (event.target == modal) {
		closeModal();
	}
}
