import collections

# Эталонные частотные таблицы (в %)
LANG_FREQS = {
    'RU': {
        'О': 10.97, 'Е': 8.45, 'А': 8.01, 'И': 7.35, 'Н': 6.70, 'Т': 6.26,
        'С': 5.47, 'Р': 4.73, 'В': 4.54, 'Л': 4.40, 'К': 3.49, 'М': 3.21,
        'Д': 2.98, 'П': 2.81, 'У': 2.62, 'Я': 2.01, 'Ы': 1.90, 'Ь': 1.74,
        'Г': 1.70, 'З': 1.65, 'Б': 1.59, 'Ч': 1.44, 'Й': 1.21, 'Х': 0.97,
        'Ж': 0.94, 'Ш': 0.73, 'Ю': 0.64, 'Ц': 0.48, 'Щ': 0.36, 'Э': 0.32,
        'Ф': 0.26, 'Ъ': 0.04, 'Ё': 0.04
    },
    'EN': {
        'E': 12.70, 'T': 9.06, 'A': 8.17, 'O': 7.51, 'I': 6.97, 'N': 6.75,
        'S': 6.33, 'H': 6.09, 'R': 5.99, 'D': 4.25, 'L': 4.03, 'C': 2.78,
        'U': 2.76, 'M': 2.41, 'W': 2.36, 'F': 2.23, 'G': 2.02, 'Y': 1.97,
        'P': 1.93, 'B': 1.29, 'V': 0.98, 'K': 0.77, 'J': 0.15, 'X': 0.15,
        'Q': 0.10, 'Z': 0.07
    }
}

SAMPLES = {
    'RU': "ЬЕЦЧУЧТАО ЕТЕРНМ — ВЧУ УЦТУЖТУО СЙЧУИ ХЕЦЭНЩХУЖПН ФХУЦЧАЪ ЭНЩХУЖ МЕСЙТА.",
    'EN': "IUHTXHQFB DQDOBVLV LV D YHUB XVHIXO PHWKRG IRU GHFUBSWLQJ VLPSOH VXEVWLWXWLRQ FLSKHUV."
}

def auto_detect_language(text):
    text_upper = text.upper()
    ru_count = sum(1 for c in text_upper if c in LANG_FREQS['RU'])
    en_count = sum(1 for c in text_upper if c in LANG_FREQS['EN'])
    return 'RU' if ru_count >= en_count else 'EN'

def analyze_text(text, lang):
    freq_dict = LANG_FREQS[lang]
    text_upper = text.upper()
    letters_in_text = [c for c in text_upper if c in freq_dict]
    total_count = len(letters_in_text)
    
    counter = collections.Counter(letters_in_text)
    stats = []
    
    for char, count in counter.most_common():
        freq_text = (count / total_count * 100) if total_count > 0 else 0
        stats.append({
            'char': char,
            'count': count,
            'freq_text': freq_text
        })
    return stats, total_count

def render_decrypted(text, key_map):
    result = []
    for c in text:
        c_upper = c.upper()
        if c_upper in key_map and key_map[c_upper]:
            # Замененная буква выводится строчной (маленькой)
            result.append(key_map[c_upper].lower())
        else:
            # Нерасшифрованная буква остается заглавной
            result.append(c)
    return "".join(result)

def print_dashboard(cipher_text, key_map, stats, total_letters, lang):
    lang_name = "РУССКИЙ" if lang == 'RU' else "ENGLISH"
    freq_dict = LANG_FREQS[lang]
    
    print("\n" + "=" * 75)
    print(f" РЕЗУЛЬТАТ РАСШИФРОВКИ [{lang_name}]:")
    print("=" * 75)
    print(render_decrypted(cipher_text, key_map))
    print("=" * 75)
    
    print(f"\n Всего букв алфавита в тексте: {total_letters}")
    print(f"{'Буква шифра':^12}|{'Кол-во':^8}|{'Частота текста':^16}|{'Эталон языка':^18}|{'Замена':^10}")
    print("-" * 72)
    
    lang_sorted_letters = list(freq_dict.keys())
    
    for i, item in enumerate(stats):
        char = item['char']
        count = item['count']
        freq = item['freq_text']
        lang_suggest = lang_sorted_letters[i] if i < len(lang_sorted_letters) else "-"
        lang_freq = freq_dict.get(lang_suggest, 0)
        current_sub = key_map.get(char, "")
        
        print(f"{char:^12}|{count:^8}|{freq:>13.2f}%  |  {lang_suggest} ({lang_freq:>5.2f}%)  |  {current_sub if current_sub else '.':^10}")

def interactive_decoder(cipher_text=None, lang=None):
    if not cipher_text:
        print("Выберите язык по умолчанию / Default language:")
        print("  1. Русский (RU)")
        print("  2. English (EN)")
        print("  3. Автоопределение по тексту (Auto)")
        l_choice = input("Выбор (1-3, по умолчанию 3): ").strip()
        
        if l_choice == '1':
            lang = 'RU'
        elif l_choice == '2':
            lang = 'EN'
        else:
            lang = None
            
        cipher_text = input("\nВведите зашифрованный текст (или Нажмите Enter для демо-текста): ").strip()
        
        if not cipher_text:
            lang = lang or 'RU'
            cipher_text = SAMPLES[lang]
        elif not lang:
            lang = auto_detect_language(cipher_text)
            
    stats, total_letters = analyze_text(cipher_text, lang)
    key_map = {}
    
    while True:
        print_dashboard(cipher_text, key_map, stats, total_letters, lang)
        print("\nКоманды:")
        print("  • Замена: Введите замену, например A=о или X=e")
        print("  • Сбросить одну букву: -A или -X")
        print("  • 3. Применить авто-гипотезу по частотности")
        print("  • 4. Очистить все замены")
        print("  • 5. Ввести новый текст / изменить язык")
        print("  • 6. Выход")
        
        choice = input("\nВведите команду или замену (напр. А=о): ").strip()
        
        if choice == '6':
            break
        elif choice == '5':
            cipher_text = input("Введите новый текст: ").strip()
            lang = auto_detect_language(cipher_text)
            stats, total_letters = analyze_text(cipher_text, lang)
            key_map.clear()
        elif choice == '3':
            lang_sorted_letters = list(LANG_FREQS[lang].keys())
            for i, item in enumerate(stats):
                if i < len(lang_sorted_letters):
                    key_map[item['char']] = lang_sorted_letters[i].lower()
            print(f" Применена гипотеза по частотности для [{lang}]!")
        elif choice == '4':
            key_map.clear()
            print(" Все замены сброшены.")
        elif choice.startswith("-") and len(choice) >= 2:
            char_to_remove = choice[1].upper()
            key_map.pop(char_to_remove, None)
        elif "=" in choice:
            parts = choice.split("=")
            if len(parts) == 2 and len(parts[0].strip()) == 1:
                cipher_char = parts[0].strip().upper()
                plain_char = parts[1].strip().lower()
                key_map[cipher_char] = plain_char
        else:
            print("Неверная команда, попробуйте еще раз.")

if __name__ == "__main__":
    print("Универсальный частотный дешифровщик (RU / EN)")
    interactive_decoder()