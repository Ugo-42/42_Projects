function allowOnlyDigits(inputEl, maxLength=3) {
    inputEl.addEventListener('input', () => {
        inputEl.value = inputEl.value.replace(/\D/g, '');
        if (inputEl.value.length > maxLength)
            inputEl.value = inputEl.value.slice(0, maxLength);
    });
    inputEl.addEventListener('focus', () => {
        if (inputEl.placeholder === '404') inputEl.placeholder = '';
    });
    inputEl.addEventListener('blur', () => {
        if (!inputEl.value) inputEl.placeholder = '404';
    });
}

const implementedCodes = [
    100,101,200,201,202,203,204,205,206,
    300,301,302,303,304,305,307,
    400,401,402,403,404,405,406,407,408,409,410,
    411,412,413,414,415,416,417,418,426,
    500,501,502,503,504,505,
];

function simulateError(inputEl, outputEl) {
    const code = parseInt(inputEl.value, 10);

    if (isNaN(code) || code < 100 || code > 599) {
        outputEl.textContent = 'Error code must be between 100 and 599';
        outputEl.style.color = '#c0392b';
        return;
    }

    const pageCode = implementedCodes.includes(code) ? code : 501;

    outputEl.textContent = `Redirecting to error page ${pageCode}...`;
    outputEl.style.color = '#20ae00ff';

    window.location.href = `/website/errors/${pageCode}.html`;
}

function showPreview(html) {
    const overlay = document.getElementById('preview-overlay');
    const iframe = document.getElementById('preview-frame');

    iframe.srcdoc = html;
    overlay.style.display = "block";
}

function uploadFile(inputEl, outputEl) {
    if (!inputEl.files.length) {
        alert('No file selected.');
        return;
    }

    const file = inputEl.files[0];

    const xhr = new XMLHttpRequest();

    xhr.open("POST", `/upload/${encodeURIComponent(file.name)}`);

    /* -------- PROGRESS -------- */
    xhr.upload.onprogress = (e) => {
        if (e.lengthComputable) {
            const percent = Math.round((e.loaded / e.total) * 100);

            document.getElementById('upload-progress').value = percent;
            document.getElementById('upload-percent').textContent = percent + "%";
        }
    };

    /* -------- SUCCESS -------- */
    xhr.onload = () => {
        outputEl.textContent = `Status: ${xhr.status} ${xhr.statusText}`;
        showPreview(xhr.responseText);
    };

    /* -------- ERROR -------- */
    xhr.onerror = () => {
        outputEl.textContent = `❌ Upload failed`;
    };

    xhr.send(file);
}

function deleteFile(inputEl, outputEl) {
    const filename = inputEl.value.trim();

    if (!filename) {
        alert('Enter filename to delete.');
        return;
    }

    fetch(`/upload/${encodeURIComponent(filename)}`, {
        method: "DELETE"
    })
    .then(async res => {
        outputEl.textContent = `Status: ${res.status} ${res.statusText}`;

        if (res.status === 204) {
            const html = `
                <html>
                    <body style="font-family:sans-serif; padding:20px;">
                        <h2>✅ File deleted successfully</h2>
                        <p><strong>${filename}</strong> has been removed.</p>
                    </body>
                </html>
            `;
            showPreview(html);
            return;
        }

        const text = await res.text();
        showPreview(text);
    })
    .catch(err => {
        outputEl.textContent = `❌ Error: ${err}`;
    });
}

function sendRequest(urlInput, methodSelect, bodyInput, output) {
    const url = urlInput.value.trim();
    const method = methodSelect.value;
    let body = bodyInput.value;
    const container = output.parentElement;

    if (!url) {
        output.textContent = "⚠️ Please enter a URL.";
        container.style.display = "block";
        return;
    }

    let options = { method, headers: {} };

    if (method !== "GET" && body) {
        options.body = body;
        options.headers['Content-Type'] = 'text/plain';
    }

    output.textContent = "";
    container.style.display = "none";

    fetch(url, options)
        .then(response => response.text()
            .then(text => {
                output.textContent =
                    `Status: ${response.status} ${response.statusText}\n\n${text}`;
                container.style.display = "block";
            })
        )
        .catch(err => {
            output.textContent = `❌ Error: ${err}`;
            container.style.display = "block";
        });
}

/* -------- DOM -------- */
const urlInput = document.getElementById('method-url');
const methodSelect = document.getElementById('method-type');
const bodyInput = document.getElementById('method-body');
const output = document.getElementById('method-output');

const previewBtn = document.getElementById('preview-btn');
const overlay = document.getElementById('preview-overlay');
const iframe = document.getElementById('preview-frame');
const closeBtn = document.getElementById('close-preview');
const sendBtn = document.getElementById('send-btn');

let lastUrl = "";

/* -------- SEND REQUEST -------- */
sendBtn.addEventListener("click", () => {
    lastUrl = urlInput.value.trim();
    sendRequest(urlInput, methodSelect, bodyInput, output);
});

/* -------- PREVIEW -------- */
previewBtn.addEventListener("click", () => {
    if (!lastUrl) return;
    overlay.style.display = "block";
    iframe.src = lastUrl;
});

/* -------- CLOSE PREVIEW -------- */
closeBtn.addEventListener("click", () => {
    overlay.style.display = "none";
    iframe.src = "";
});
