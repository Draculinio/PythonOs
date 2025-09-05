// ========================================
// EFECTOS RETRO PARA MKDOCS
// ========================================

document.addEventListener('DOMContentLoaded', function() {
    
    // ========================================
    // EFECTO TYPING EN TÍTULOS PRINCIPALES
    // ========================================
    const mainTitle = document.querySelector('h1');
    if (mainTitle && !mainTitle.classList.contains('typed')) {
        mainTitle.classList.add('typing-effect');
        mainTitle.classList.add('typed');
    }

    // ========================================
    // CURSOR PARPADEANTE EN CÓDIGO
    // ========================================
    const codeBlocks = document.querySelectorAll('pre code');
    codeBlocks.forEach(block => {
        // Agregar prompt de terminal
        if (!block.querySelector('.terminal-prompt')) {
            const prompt = document.createElement('span');
            prompt.className = 'terminal-prompt';
            prompt.innerHTML = '<span style="color: #00ff41;">user@sistema</span><span style="color: #00ffff;">:</span><span style="color: #ffb000;">~$</span> ';
            block.insertBefore(prompt, block.firstChild);
        }
    });

    // ========================================
    // EFECTOS DE HOVER EN NAVEGACIÓN
    // ========================================
    const navLinks = document.querySelectorAll('.md-nav__link');
    navLinks.forEach(link => {
        link.addEventListener('mouseenter', function() {
            this.style.textShadow = '0 0 8px currentColor';
        });
        
        link.addEventListener('mouseleave', function() {
            if (!this.classList.contains('md-nav__link--active')) {
                this.style.textShadow = '';
            }
        });
    });

    // ========================================
    // EFECTO MATRIX EN BACKGROUND (SUTIL)
    // ========================================
    function createMatrixEffect() {
        const canvas = document.createElement('canvas');
        const ctx = canvas.getContext('2d');
        
        canvas.style.position = 'fixed';
        canvas.style.top = '0';
        canvas.style.left = '0';
        canvas.style.width = '100%';
        canvas.style.height = '100%';
        canvas.style.pointerEvents = 'none';
        canvas.style.zIndex = '-1';
        canvas.style.opacity = '0.05';
        
        document.body.appendChild(canvas);
        
        function resizeCanvas() {
            canvas.width = window.innerWidth;
            canvas.height = window.innerHeight;
        }
        
        resizeCanvas();
        window.addEventListener('resize', resizeCanvas);
        
        const characters = '01アイウエオカキクケコサシスセソタチツテトナニヌネノハヒフヘホマミムメモヤユヨラリルレロワヲン';
        const fontSize = 14;
        const columns = canvas.width / fontSize;
        const drops = Array(Math.floor(columns)).fill(1);
        
        function draw() {
            ctx.fillStyle = 'rgba(0, 0, 0, 0.05)';
            ctx.fillRect(0, 0, canvas.width, canvas.height);
            
            ctx.fillStyle = '#00ff41';
            ctx.font = fontSize + 'px monospace';
            
            for (let i = 0; i < drops.length; i++) {
                const text = characters[Math.floor(Math.random() * characters.length)];
                ctx.fillText(text, i * fontSize, drops[i] * fontSize);
                
                if (drops[i] * fontSize > canvas.height && Math.random() > 0.975) {
                    drops[i] = 0;
                }
                drops[i]++;
            }
        }
        
        // Solo ejecutar si el usuario prefiere animaciones
        if (!window.matchMedia('(prefers-reduced-motion: reduce)').matches) {
            setInterval(draw, 100);
        }
    }

    // Activar efecto matrix solo en páginas específicas (opcional)
    if (document.body.classList.contains('matrix-bg')) {
        createMatrixEffect();
    }

    // ========================================
    // SONIDOS RETRO (OPCIONALES)
    // ========================================
    function playBeep() {
        // Solo si el usuario no tiene preferencias de movimiento reducido
        if (window.matchMedia('(prefers-reduced-motion: reduce)').matches) return;
        
        const audioContext = new (window.AudioContext || window.webkitAudioContext)();
        const oscillator = audioContext.createOscillator();
        const gainNode = audioContext.createGain();
        
        oscillator.connect(gainNode);
        gainNode.connect(audioContext.destination);
        
        oscillator.frequency.value = 800;
        oscillator.type = 'square';
        
        gainNode.gain.setValueAtTime(0.1, audioContext.currentTime);
        gainNode.gain.exponentialRampToValueAtTime(0.01, audioContext.currentTime + 0.1);
        
        oscillator.start(audioContext.currentTime);
        oscillator.stop(audioContext.currentTime + 0.1);
    }

    // Agregar sonido a clicks en navegación (muy sutil)
    const importantLinks = document.querySelectorAll('.md-tabs__link, .md-nav__link--active');
    importantLinks.forEach(link => {
        link.addEventListener('click', playBeep);
    });

    // ========================================
    // EASTER EGG - KONAMI CODE
    // ========================================
    let konamiCode = [];
    const konamiSequence = [38, 38, 40, 40, 37, 39, 37, 39, 66, 65]; // ↑↑↓↓←→←→BA
    
    document.addEventListener('keydown', function(e) {
        konamiCode.push(e.keyCode);
        
        if (konamiCode.length > konamiSequence.length) {
            konamiCode.shift();
        }
        
        if (konamiCode.length === konamiSequence.length && 
            konamiCode.every((code, index) => code === konamiSequence[index])) {
            
            // Activar efectos especiales
            document.body.style.animation = 'rainbow 2s infinite';
            document.body.classList.add('matrix-bg');
            createMatrixEffect();
            
            // Mostrar mensaje
            const message = document.createElement('div');
            message.innerHTML = '🎉 ¡MODO RETRO ACTIVADO! 🎉';
            message.style.cssText = `
                position: fixed;
                top: 50%;
                left: 50%;
                transform: translate(-50%, -50%);
                background: #000;
                color: #00ff41;
                padding: 20px;
                border: 3px solid #00ff41;
                font-family: monospace;
                font-size: 24px;
                text-shadow: 0 0 10px #00ff41;
                z-index: 9999;
                animation: blink 0.5s infinite;
            `;
            
            document.body.appendChild(message);
            
            setTimeout(() => {
                document.body.removeChild(message);
            }, 3000);
            
            konamiCode = [];
        }
    });

    // CSS para el efecto rainbow
    const style = document.createElement('style');
    style.textContent = `
        @keyframes rainbow {
            0% { filter: hue-rotate(0deg); }
            100% { filter: hue-rotate(360deg); }
        }
    `;
    document.head.appendChild(style);

    console.log('%c¡Sistema operativo documentado! 🚀', 'color: #00ff41; font-size: 16px; font-weight: bold;');
    console.log('%cTip: Prueba el código Konami... ↑↑↓↓←→←→BA', 'color: #00ffff; font-size: 12px;');
});