import os
import sys
import time
import json
import logging
import random
from logging.handlers import RotatingFileHandler
from pathlib import Path
from typing import Optional, List, Dict, Any

def setup_qt_plugins():
    try:
        import PyQt5
        qt5_path = os.path.dirname(PyQt5.__file__)
        
        possible_paths = [
            os.path.join(qt5_path, 'Qt5', 'plugins'),
            os.path.join(qt5_path, 'Qt', 'plugins'),
        ]
        
        for path in possible_paths:
            platforms_path = os.path.join(path, 'platforms')
            if os.path.exists(platforms_path):
                os.environ['QT_QPA_PLATFORM_PLUGIN_PATH'] = path
                return path
        return None
        
    except ImportError:
        return None

setup_qt_plugins()

try:
    from PyQt5 import QtWidgets, QtGui, QtCore
except ImportError:
    sys.exit(1)

APP_DIR = Path(__file__).parent
DATA_DIR = APP_DIR / "data"
ASSETS_DIR = APP_DIR / "assets" / "images"
DEFAULT_TEST_FILE = APP_DIR / "data" / "tests.json"
STYLESHEET = APP_DIR / "styles.qss"

LOG_DIR = APP_DIR / "logs"
LOG_DIR.mkdir(exist_ok=True)
logger = logging.getLogger("InteractiveTests")
logger.setLevel(logging.DEBUG)
rh = RotatingFileHandler(LOG_DIR / "app.log", maxBytes=2_000_000, backupCount=5, encoding="utf-8")
fmt = logging.Formatter("%(asctime)s %(levelname)s %(name)s: %(message)s")
rh.setFormatter(fmt)
logger.addHandler(rh)

def load_json_safe(path: Path) -> Optional[Any]:
    try:
        text = path.read_text(encoding="utf-8-sig")
        return json.loads(text)
    except Exception:
        return None

def load_text_file(path: Path) -> Optional[str]:
    encodings = ['utf-8', 'utf-8-sig', 'cp1251']
    for encoding in encodings:
        try:
            return path.read_text(encoding=encoding)
        except Exception:
            continue
    return None

def resolve_image_field(image_field: str, base_path: str) -> Optional[str]:
    if not image_field:
        return None
    if image_field.startswith(('http://', 'https://')):
        return None
    if os.path.isabs(image_field):
        if os.path.exists(image_field):
            return image_field
        return None
    path_from_base = os.path.join(base_path, image_field)
    if os.path.exists(path_from_base):
        return path_from_base
    path_from_app = os.path.join(str(APP_DIR), image_field)
    if os.path.exists(path_from_app):
        return path_from_app
    return None

def load_tests_from_file(filepath: Path) -> Dict[str, Any]:
    data = load_json_safe(filepath)
    if not data:
        return {"tests": [], "_base_path": str(filepath.parent)}
    if isinstance(data, dict) and "tests" not in data and "questions" in data:
        data = {"tests": [data]}
    if isinstance(data, dict) and "tests" in data:
        data["_base_path"] = str(filepath.parent)
        for t in data["tests"]:
            if isinstance(t, dict):
                t["_source_base"] = str(filepath.parent)
        return data
    if isinstance(data, list):
        res = {"tests": [], "_base_path": str(filepath.parent)}
        for t in data:
            if isinstance(t, dict):
                t["_source_base"] = str(filepath.parent)
                res["tests"].append(t)
        return res
    return {"tests": [], "_base_path": str(filepath.parent)}

def calculate_grade_10(correct_count: int, total_questions: int) -> int:
    """Рассчитывает оценку по 10-балльной системе для отдельных тестов"""
    if total_questions == 0:
        return 0
    percentage = (correct_count / total_questions) * 100
    if percentage >= 95: return 10
    elif percentage >= 85: return 9
    elif percentage >= 75: return 8
    elif percentage >= 65: return 7
    elif percentage >= 55: return 6
    elif percentage >= 45: return 5
    elif percentage >= 35: return 4
    elif percentage >= 25: return 3
    elif percentage >= 15: return 2
    elif percentage >= 5: return 1
    else: return 0

def calculate_final_grade_10(test_results: List[Dict[str, Any]]) -> int:
    """
    Рассчитывает итоговую оценку по 10-балльной системе на основе всех тестов
    Входной тест: 50% от итоговой оценки
    Итоговый тест: 50% от итоговой оценки
    """
    if not test_results:
        return 0
    
    initial_test_score = 0
    final_test_score = 0
    initial_test_weight = 0.5  # 50%
    final_test_weight = 0.5    # 50%
    
    for result in test_results:
        test_type = result.get('type', '')
        correct_count = result.get('correct_count', 0)
        total_questions = result.get('total_questions', 1)
        
        # Рассчитываем процент выполнения для каждого теста
        percentage = (correct_count / total_questions) * 100 if total_questions > 0 else 0
        
        if test_type == 'initial':
            initial_test_score = percentage
        elif test_type == 'final':
            final_test_score = percentage
    
    # Рассчитываем итоговый балл по 10-балльной системе
    final_percentage = (initial_test_score * initial_test_weight) + (final_test_score * final_test_weight)
    
    # Преобразуем процент в 10-балльную систему
    final_grade = calculate_grade_10(
        round((final_percentage / 100) * 20),  # Эмулируем как будто было 20 вопросов
        20
    )
    
    return min(final_grade, 10)  # Ограничиваем максимум 10 баллами

def get_grade_description_10(grade: int) -> str:
    """Возвращает текстовое описание оценки по 10-балльной системе"""
    if grade >= 9:
        return "Отлично! 🎉"
    elif grade >= 7:
        return "Очень хорошо! 👍"
    elif grade >= 5:
        return "Хорошо 🙂"
    elif grade >= 3:
        return "Удовлетворительно 😐"
    else:
        return "Неудовлетворительно 😕"

def shuffle_questions(questions: List[Dict[str, Any]]) -> List[Dict[str, Any]]:
    shuffled_questions = questions.copy()
    random.shuffle(shuffled_questions)
    for question in shuffled_questions:
        if 'options' in question:
            options = question['options']
            correct_answer = question.get('correct')
            if correct_answer is not None:
                if isinstance(correct_answer, int):
                    indexed_options = list(enumerate(options))
                    random.shuffle(indexed_options)
                    new_options = [opt for _, opt in indexed_options]
                    for new_idx, (old_idx, _) in enumerate(indexed_options):
                        if old_idx == correct_answer:
                            question['correct'] = new_idx
                            break
                    question['options'] = new_options
                elif isinstance(correct_answer, list):
                    indexed_options = list(enumerate(options))
                    random.shuffle(indexed_options)
                    new_options = [opt for _, opt in indexed_options]
                    new_correct = []
                    for old_idx in correct_answer:
                        for new_idx, (orig_idx, _) in enumerate(indexed_options):
                            if orig_idx == old_idx:
                                new_correct.append(new_idx)
                                break
                    question['correct'] = sorted(new_correct)
                    question['options'] = new_options
                elif isinstance(correct_answer, str):
                    random.shuffle(options)
                    question['options'] = options
        for field in ['choices', 'answers']:
            if field in question:
                options = question[field]
                random.shuffle(options)
                question[field] = options
    return shuffled_questions

class TheoryWidget(QtWidgets.QWidget):
    def __init__(self, theory_content, base_path, parent=None):
        super().__init__(parent)
        self.base_path = base_path
        self.setup_ui(theory_content)
    
    def setup_ui(self, theory_content):
        layout = QtWidgets.QVBoxLayout(self)
        
        scroll = QtWidgets.QScrollArea()
        scroll.setWidgetResizable(True)
        
        content_widget = QtWidgets.QWidget()
        content_layout = QtWidgets.QVBoxLayout(content_widget)
        content_layout.setSpacing(15)
        content_layout.setContentsMargins(10, 10, 10, 10)
        
        sections = self.parse_theory_content(theory_content)
        
        for section in sections:
            frame = QtWidgets.QFrame()
            frame.setObjectName("theoryCard")
            frame_layout = QtWidgets.QVBoxLayout(frame)
            frame_layout.setSpacing(10)
            frame_layout.setContentsMargins(15, 15, 15, 15)
            
            title_text = section.get("title", "")
            if title_text:
                title_label = QtWidgets.QLabel(title_text)
                title_label.setObjectName("theoryTitle")
                title_label.setWordWrap(True)
                frame_layout.addWidget(title_label)
            
            text_content = section.get("text", "")
            if text_content:
                text_label = QtWidgets.QLabel(text_content)
                text_label.setObjectName("theoryText")
                text_label.setWordWrap(True)
                text_label.setTextFormat(QtCore.Qt.PlainText)
                frame_layout.addWidget(text_label)
            
            images = section.get("images", [])
            if "image" in section and section["image"]:
                images.append(section["image"])
            
            for img_field in images:
                if img_field:
                    imgpath = resolve_image_field(img_field, self.base_path)
                    if imgpath and os.path.exists(imgpath):
                        pixmap = QtGui.QPixmap(imgpath)
                        if not pixmap.isNull():
                            img_label = QtWidgets.QLabel()
                            img_label.setObjectName("theory_image")
                            
                            # Адаптивное масштабирование под ширину окна
                            screen_width = QtWidgets.QApplication.primaryScreen().availableGeometry().width()
                            max_width = int(screen_width * 0.6)  # 60% ширины экрана
                            scaled_pixmap = pixmap.scaledToWidth(max_width, QtCore.Qt.SmoothTransformation)
                            img_label.setPixmap(scaled_pixmap)
                            img_label.setAlignment(QtCore.Qt.AlignCenter)
                            frame_layout.addWidget(img_label)
            
            content_layout.addWidget(frame)
        
        content_layout.addStretch()
        scroll.setWidget(content_widget)
        layout.addWidget(scroll)

    def parse_theory_content(self, theory_content):
        sections = []
        if isinstance(theory_content, dict):
            if "sections" in theory_content:
                sections = theory_content["sections"]
            elif "title" in theory_content or "text" in theory_content:
                sections = [theory_content]
        elif isinstance(theory_content, list):
            sections = theory_content
        else:
            sections = [{"title": "Теория", "text": str(theory_content)}]
        
        if not sections:
            sections = [{"title": "Теория", "text": "Теоретические материалы отсутствуют."}]
        
        return sections

class FullscreenImageViewer(QtWidgets.QMainWindow):
    """Окно полноэкранного просмотра изображений"""
    
    def __init__(self, pixmap, image_name, parent=None):
        super().__init__(parent)
        self.pixmap = pixmap
        self.image_name = image_name
        self.setup_ui()
    
    def setup_ui(self):
        self.setWindowTitle("Просмотр изображения - ESC для выхода")
        
        # Центральный виджет
        central_widget = QtWidgets.QWidget()
        self.setCentralWidget(central_widget)
        layout = QtWidgets.QVBoxLayout(central_widget)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # Область прокрутки для изображения
        self.scroll_area = QtWidgets.QScrollArea()
        self.scroll_area.setWidgetResizable(True)
        self.scroll_area.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAsNeeded)
        self.scroll_area.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAsNeeded)
        
        # Метка для изображения
        self.image_label = QtWidgets.QLabel()
        self.image_label.setAlignment(QtCore.Qt.AlignCenter)
        self.image_label.setScaledContents(False)
        
        self.scroll_area.setWidget(self.image_label)
        layout.addWidget(self.scroll_area)
        
        # Показываем изображение
        self.show_fullscreen_image()
    
    def show_fullscreen_image(self):
        """Показ изображения на полный экран"""
        if self.pixmap and not self.pixmap.isNull():
            # Получаем размеры экрана
            screen = QtWidgets.QApplication.primaryScreen()
            screen_geometry = screen.availableGeometry()
            
            # Масштабируем изображение под размер экрана с сохранением пропорций
            scaled_pixmap = self.pixmap.scaled(
                screen_geometry.width(),
                screen_geometry.height(),
                QtCore.Qt.KeepAspectRatio,
                QtCore.Qt.SmoothTransformation
            )
            
            self.image_label.setPixmap(scaled_pixmap)
            self.image_label.resize(scaled_pixmap.size())
    
    def keyPressEvent(self, event):
        """Обработка нажатий клавиш"""
        if event.key() == QtCore.Qt.Key_Escape:
            self.close()
        elif event.key() == QtCore.Qt.Key_Left:
            if self.parent():
                self.parent().previous_image()
                self.update_image(self.parent().current_pixmap, self.parent().images[self.parent().current_image_index])
        elif event.key() == QtCore.Qt.Key_Right:
            if self.parent():
                self.parent().next_image()
                self.update_image(self.parent().current_pixmap, self.parent().images[self.parent().current_image_index])
        else:
            super().keyPressEvent(event)
    
    def update_image(self, pixmap, image_name):
        """Обновление изображения"""
        self.pixmap = pixmap
        self.image_name = image_name
        self.show_fullscreen_image()
    
    def wheelEvent(self, event):
        """Масштабирование колесиком мыши"""
        if event.angleDelta().y() > 0:
            self.zoom_in()
        else:
            self.zoom_out()
    
    def zoom_in(self):
        """Увеличение изображения на 20%"""
        current_pixmap = self.image_label.pixmap()
        if current_pixmap and not current_pixmap.isNull():
            new_size = current_pixmap.size() * 1.2
            scaled_pixmap = self.pixmap.scaled(
                new_size,
                QtCore.Qt.KeepAspectRatio,
                QtCore.Qt.SmoothTransformation
            )
            self.image_label.setPixmap(scaled_pixmap)
            self.image_label.resize(scaled_pixmap.size())
    
    def zoom_out(self):
        """Уменьшение изображения на 20%"""
        current_pixmap = self.image_label.pixmap()
        if current_pixmap and not current_pixmap.isNull():
            new_size = current_pixmap.size() * 0.8
            scaled_pixmap = self.pixmap.scaled(
                new_size,
                QtCore.Qt.KeepAspectRatio,
                QtCore.Qt.SmoothTransformation
            )
            self.image_label.setPixmap(scaled_pixmap)
            self.image_label.resize(scaled_pixmap.size())

class PracticeWidget(QtWidgets.QWidget):
    def __init__(self, practice_data, base_path, main_window=None):
        super().__init__()
        self.main_window = main_window  # Сохраняем ссылку на главное окно
        self.practice_data = practice_data
        self.base_path = base_path
        self.current_task_index = 0
        self.current_image_index = 0
        self.images = []
        self.current_pixmap = None
        self.form_data = {}
        self.form_results = {}  # Храним результаты проверки
        self.form_widgets = {}
        self.fullscreen_viewer = None
        self.setup_ui()
    
    def setup_ui(self):
        layout = QtWidgets.QVBoxLayout(self)
        
        self.tab_widget = QtWidgets.QTabWidget()
        
        self.theory_tab = QtWidgets.QWidget()
        self.table_tab = QtWidgets.QWidget()
        self.images_tab = QtWidgets.QWidget()
        self.form_tab = QtWidgets.QWidget()
        self.results_tab = QtWidgets.QWidget()
        
        self.tab_widget.addTab(self.theory_tab, "Теория")
        self.tab_widget.addTab(self.table_tab, "Таблица")
        self.tab_widget.addTab(self.images_tab, "Изображения")
        self.tab_widget.addTab(self.form_tab, "Протокол")
        self.tab_widget.addTab(self.results_tab, "Результаты")
        
        self.setup_theory_tab()
        self.setup_table_tab()
        self.setup_images_tab()
        self.setup_form_tab()
        self.setup_results_tab()
        
        layout.addWidget(self.tab_widget)
        
        nav_layout = QtWidgets.QHBoxLayout()
        self.prev_btn = QtWidgets.QPushButton("← Назад")
        self.prev_btn.clicked.connect(self.previous_task)
        self.next_btn = QtWidgets.QPushButton("Далее →")
        self.next_btn.clicked.connect(self.next_task)
        self.task_label = QtWidgets.QLabel("Задание 1 из 3")
        
        # Кнопка проверки
        self.check_btn = QtWidgets.QPushButton("Проверить ответы")
        self.check_btn.clicked.connect(self.check_answers)
        
        nav_layout.addWidget(self.prev_btn)
        nav_layout.addWidget(self.task_label)
        nav_layout.addStretch()
        nav_layout.addWidget(self.check_btn)
        nav_layout.addWidget(self.next_btn)
        
        layout.addLayout(nav_layout)
        self.update_task_display()
    
    def setup_results_tab(self):
        """Вкладка с результатами проверки"""
        layout = QtWidgets.QVBoxLayout(self.results_tab)
        
        self.results_label = QtWidgets.QLabel("Результаты проверки появятся здесь после нажатия кнопки 'Проверить ответы'")
        self.results_label.setWordWrap(True)
        self.results_label.setAlignment(QtCore.Qt.AlignCenter)
        layout.addWidget(self.results_label)
        
        # Таблица с результатами
        self.results_table = QtWidgets.QTableWidget()
        self.results_table.setColumnCount(3)
        self.results_table.setHorizontalHeaderLabels(["Поле", "Ваш ответ", "Результат"])
        layout.addWidget(self.results_table)
        
        # Общий результат
        self.final_result_label = QtWidgets.QLabel()
        self.final_result_label.setAlignment(QtCore.Qt.AlignCenter)
        layout.addWidget(self.final_result_label)
    
    def check_answers(self):
        """Проверка правильности ответов"""
        task = self.practice_data[self.current_task_index]
        form_config = task.get("form", {})
        fields = form_config.get("fields", [])
        
        correct_count = 0
        total_fields = 0
        results = []
        
        for field in fields:
            field_label = field["label"]
            field_type = field["type"]
            
            if field_type == "double":
                for subfield in field.get("subfields", []):
                    if "correct_answer" in subfield:
                        total_fields += 1
                        field_key = f"{field_label}_{subfield['label']}"
                        user_answer = self.form_widgets.get(field_key, "").text().strip() if hasattr(self.form_widgets.get(field_key), 'text') else str(self.form_widgets.get(field_key, ""))
                        correct_answer = subfield["correct_answer"]
                        
                        is_correct = user_answer == correct_answer
                        if is_correct:
                            correct_count += 1
                        
                        results.append({
                            "field": f"{field_label} - {subfield['label']}",
                            "user_answer": user_answer,
                            "correct_answer": correct_answer,
                            "is_correct": is_correct,
                            "hint": subfield.get("hint", "")
                        })
            
            elif field_type == "select":
                if "correct_answer" in field:
                    total_fields += 1
                    field_key = field["label"]
                    widget = self.form_widgets.get(field_key)
                    user_answer = widget.currentText() if widget else ""
                    correct_answer = field["correct_answer"]
                    
                    is_correct = user_answer == correct_answer
                    if is_correct:
                        correct_count += 1
                    
                    results.append({
                        "field": field_label,
                        "user_answer": user_answer,
                        "correct_answer": correct_answer,
                        "is_correct": is_correct,
                        "hint": field.get("hint", "")
                    })
        
        # Сохраняем результаты
        task_key = f"task_{self.current_task_index}"
        is_passed = correct_count == total_fields
        self.form_results[task_key] = {
            "correct_count": correct_count,
            "total_fields": total_fields,
            "is_passed": is_passed,
            "results": results
        }
        
        # Показываем результаты
        self.show_results(results, correct_count, total_fields)
        
        # Получаем правила валидации
        validation_rules = form_config.get("validation_rules", {})
        required_correct = validation_rules.get("correct_answers_required", total_fields)
        
        # Блокируем/разблокируем кнопку далее
        if correct_count >= required_correct:
            self.next_btn.setEnabled(True)
            
            # Если это последнее задание и оно выполнено, предлагаем переход к итоговому тесту
            if self.current_task_index == len(self.practice_data) - 1 and is_passed:
                # Автоматически переходим к итоговому тесту через короткую задержку
                QtCore.QTimer.singleShot(500, self.finish_practice_and_go_to_final_test)
        else:
            self.next_btn.setEnabled(False)
            QtWidgets.QMessageBox.warning(self, "Ошибка", 
                f"Задание выполнено неверно! Правильных ответов: {correct_count} из {total_fields}. "
                f"Исправьте ошибки и попробуйте снова.")
    
    def show_results(self, results, correct_count, total_fields):
        """Показывает подробные результаты проверки"""
        self.results_table.setRowCount(len(results))
        
        for row, result in enumerate(results):
            self.results_table.setItem(row, 0, QtWidgets.QTableWidgetItem(result["field"]))
            self.results_table.setItem(row, 1, QtWidgets.QTableWidgetItem(result["user_answer"]))
            
            result_item = QtWidgets.QTableWidgetItem()
            if result["is_correct"]:
                result_item.setText("✓ Верно")
                result_item.setBackground(QtGui.QColor(144, 238, 144))  # Светло-зеленый
            else:
                result_item.setText(f"✗ Неверно (правильно: {result['correct_answer']})")
                result_item.setBackground(QtGui.QColor(255, 182, 193))  # Светло-красный
                # Добавляем подсказку как tooltip
                if result["hint"]:
                    result_item.setToolTip(result["hint"])
            
            self.results_table.setItem(row, 2, result_item)
        
        self.results_table.resizeColumnsToContents()
        
        # Общий результат - исправленная логика
        if correct_count == total_fields:
            self.final_result_label.setText("🎉 Все ответы верны! Задание выполнено успешно.")
        else:
            validation_rules = self.practice_data[self.current_task_index].get("form", {}).get("validation_rules", {})
            required_correct = validation_rules.get("correct_answers_required", total_fields)
            
            if correct_count >= required_correct:
                self.final_result_label.setText(
                    f"✅ Задание выполнено! Правильных ответов: {correct_count} из {total_fields}\n"
                    f"Минимальное требование: {required_correct} правильных ответов"
                )
            else:
                self.final_result_label.setText(
                    f"❌ Задание не выполнено. Правильных ответов: {correct_count} из {total_fields}\n"
                    f"Требуется минимум {required_correct} правильных ответов. Исправьте ошибки и проверьте снова."
                )
        
        # Переключаем на вкладку результатов
        self.tab_widget.setCurrentIndex(4)  # Индекс вкладки "Результаты"
    
    def next_task(self):
        """Переход к следующему заданию с проверкой выполнения текущего"""
        task_key = f"task_{self.current_task_index}"
        current_result = self.form_results.get(task_key, {})
        
        # Проверяем, выполнено ли текущее задание
        if not current_result.get("is_passed", False):
            QtWidgets.QMessageBox.warning(self, "Внимание", 
                "Сначала выполните текущее задание правильно!")
            return
        
        # Если это не последнее задание, переходим к следующему
        if self.current_task_index < len(self.practice_data) - 1:
            self.current_task_index += 1
            self.update_task_display()
        else:
            # Это последнее задание - переходим к итоговому тесту
            self.finish_practice_and_go_to_final_test()

    def finish_practice_and_go_to_final_test(self):
        """Завершение практических заданий и переход к итоговому тесту"""
        # Проверяем, что все задания выполнены
        all_passed = all(
            self.form_results.get(f"task_{i}", {}).get("is_passed", False)
            for i in range(len(self.practice_data))
        )
        
        if all_passed:
            # Создаем кастомный диалог с кнопками Да/Нет
            msg_box = QtWidgets.QMessageBox()
            msg_box.setWindowTitle("Поздравляем!")
            msg_box.setText("Все практические задания выполнены успешно!\nПерейти к итоговому тесту?")
            msg_box.setIcon(QtWidgets.QMessageBox.Question)
            
            # Создаем кастомные кнопки
            yes_button = msg_box.addButton("Да", QtWidgets.QMessageBox.YesRole)
            no_button = msg_box.addButton("Нет", QtWidgets.QMessageBox.NoRole)
            
            msg_box.exec_()
            
            if msg_box.clickedButton() == yes_button:
                if self.main_window:
                    self.main_window.next_stage()
        else:
            QtWidgets.QMessageBox.warning(self, "Внимание", 
                "Не все задания выполнены! Завершите все практические задания.")
    
    def previous_task(self):
        """Переход к предыдущему заданию"""
        if self.current_task_index > 0:
            self.current_task_index -= 1
            self.update_task_display()

    def setup_theory_tab(self):
        layout = QtWidgets.QVBoxLayout(self.theory_tab)
        self.theory_content = QtWidgets.QTextEdit()
        self.theory_content.setReadOnly(True)
        layout.addWidget(self.theory_content)
    
    def setup_table_tab(self):
        layout = QtWidgets.QVBoxLayout(self.table_tab)
        self.table_content = QtWidgets.QTextEdit()
        self.table_content.setReadOnly(True)
        layout.addWidget(self.table_content)
    
    def setup_images_tab(self):
        """Настройка вкладки с изображениями в полноэкранном режиме"""
        layout = QtWidgets.QVBoxLayout(self.images_tab)
        
        # Панель навигации по изображениям
        image_nav_layout = QtWidgets.QHBoxLayout()
        
        self.prev_image_btn = QtWidgets.QPushButton("← Предыдущее")
        self.prev_image_btn.clicked.connect(self.previous_image)
        image_nav_layout.addWidget(self.prev_image_btn)
        
        self.image_counter = QtWidgets.QLabel("Изображение 1 из 1")
        image_nav_layout.addWidget(self.image_counter)
        
        self.next_image_btn = QtWidgets.QPushButton("Следующее →")
        self.next_image_btn.clicked.connect(self.next_image)
        image_nav_layout.addWidget(self.next_image_btn)
        
        image_nav_layout.addStretch()
        
        # Кнопка полноэкранного режима
        self.fullscreen_btn = QtWidgets.QPushButton("🖵 Полный экран")
        self.fullscreen_btn.clicked.connect(self.toggle_fullscreen)
        image_nav_layout.addWidget(self.fullscreen_btn)
        
        layout.addLayout(image_nav_layout)
        
        # Область для отображения изображения
        self.image_scroll = QtWidgets.QScrollArea()
        self.image_scroll.setWidgetResizable(True)
        self.image_scroll.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAsNeeded)
        self.image_scroll.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAsNeeded)
        
        self.image_label = QtWidgets.QLabel()
        self.image_label.setAlignment(QtCore.Qt.AlignCenter)
        self.image_label.setScaledContents(False)
        
        # Делаем изображение кликабельным для полноэкранного режима
        self.image_label.mousePressEvent = self.image_clicked
        
        self.image_scroll.setWidget(self.image_label)
        layout.addWidget(self.image_scroll)
        
        # Подпись к изображению
        self.image_caption = QtWidgets.QLabel()
        self.image_caption.setAlignment(QtCore.Qt.AlignCenter)
        self.image_caption.setObjectName("imageCaption")
        layout.addWidget(self.image_caption)
    
    def setup_form_tab(self):
        """Настройка вкладки с формой для заполнения"""
        layout = QtWidgets.QVBoxLayout(self.form_tab)
        
        self.form_scroll = QtWidgets.QScrollArea()
        self.form_scroll.setWidgetResizable(True)
        
        self.form_container = QtWidgets.QWidget()
        self.form_layout = QtWidgets.QVBoxLayout(self.form_container)
        
        self.form_scroll.setWidget(self.form_container)
        layout.addWidget(self.form_scroll)
    
    def update_task_display(self):
        """Обновление отображения для текущего задания"""
        if not self.practice_data or self.current_task_index >= len(self.practice_data):
            return
        
        task = self.practice_data[self.current_task_index]
        
        self.task_label.setText(f"Задание {self.current_task_index + 1} из {len(self.practice_data)}")
        
        theory_text = task.get("theory", "")
        table_text = task.get("table", "")
        
        self.theory_content.setHtml(f"<h3>Теоретическая часть</h3><p>{theory_text.replace(chr(10), '<br>')}</p>")
        self.table_content.setHtml(f"<h3>Табличные данные</h3><p>{table_text.replace(chr(10), '<br>')}</p>")
        
        self.update_images_display(task)
        self.update_form_display(task)
        
        self.prev_btn.setEnabled(self.current_task_index > 0)
        self.next_btn.setEnabled(False)  # Сначала нужно выполнить задание
        
        # Сбрасываем результаты для нового задания
        self.tab_widget.setCurrentIndex(0)  # Переключаем на вкладку теории
        
        # Очищаем таблицу результатов
        self.results_table.setRowCount(0)
        self.final_result_label.setText("")
        self.results_label.setText("Результаты проверки появятся здесь после нажатия кнопки 'Проверить ответы'")
    
    def update_images_display(self, task):
        """Обновление отображения изображений для текущего задания"""
        self.images = task.get("images", [])
        self.current_image_index = 0
        
        if not self.images:
            self.image_label.setText("Изображения отсутствуют для данного задания")
            self.image_caption.setText("")
            self.prev_image_btn.setEnabled(False)
            self.next_image_btn.setEnabled(False)
            self.fullscreen_btn.setEnabled(False)
            self.image_counter.setText("Изображения отсутствуют")
            return
        
        # Показываем первое изображение
        self.show_current_image()
        
        # Настраиваем кнопки навигации
        self.prev_image_btn.setEnabled(len(self.images) > 1)
        self.next_image_btn.setEnabled(len(self.images) > 1)
        self.fullscreen_btn.setEnabled(True)
    
    def show_current_image(self):
        """Показ текущего изображения в высоком качестве"""
        if not self.images or self.current_image_index >= len(self.images):
            return
        
        img_field = self.images[self.current_image_index]
        if not img_field:
            return
        
        imgpath = resolve_image_field(img_field, self.base_path)
        if imgpath and os.path.exists(imgpath):
            try:
                # Загружаем изображение в оригинальном размере
                self.current_pixmap = QtGui.QPixmap(imgpath)
                if not self.current_pixmap.isNull():
                    # Получаем размеры области прокрутки
                    viewport_size = self.image_scroll.viewport().size()
                    
                    # Масштабируем с сохранением пропорций (90% высоты viewport)
                    scaled_pixmap = self.current_pixmap.scaled(
                        viewport_size.width() - 50,
                        viewport_size.height() - 50,
                        QtCore.Qt.KeepAspectRatio,
                        QtCore.Qt.SmoothTransformation
                    )
                    
                    self.image_label.setPixmap(scaled_pixmap)
                    self.image_label.resize(scaled_pixmap.size())
                    
                    # Обновляем подпись и счетчик
                    self.image_caption.setText(os.path.basename(imgpath))
                    self.image_counter.setText(f"Изображение {self.current_image_index + 1} из {len(self.images)}")
                    return
            except Exception as e:
                print(f"Ошибка загрузки изображения: {e}")
        
        # Если изображение не загрузилось
        self.image_label.setText(f"Не удалось загрузить изображение: {os.path.basename(imgpath)}")
        self.image_caption.setText("")
        self.current_pixmap = None
    
    def previous_image(self):
        """Переход к предыдущему изображению"""
        if len(self.images) > 1:
            self.current_image_index = (self.current_image_index - 1) % len(self.images)
            self.show_current_image()
    
    def next_image(self):
        """Переход к следующему изображению"""
        if len(self.images) > 1:
            self.current_image_index = (self.current_image_index + 1) % len(self.images)
            self.show_current_image()
    
    def image_clicked(self, event):
        """Обработка клика по изображению"""
        self.toggle_fullscreen()
    
    def toggle_fullscreen(self):
        """Переключение полноэкранного режима"""
        if hasattr(self, 'current_pixmap') and self.current_pixmap and not self.current_pixmap.isNull():
            self.fullscreen_viewer = FullscreenImageViewer(
                self.current_pixmap, 
                self.images[self.current_image_index] if self.images else "",
                self
            )
            self.fullscreen_viewer.showFullScreen()
    
    def update_form_display(self, task):
        """Обновление формы для текущего задания"""
        # Очищаем предыдущую форму
        self.clear_form_layout()
        
        form_config = task.get("form", {})
        if not form_config:
            no_form_label = QtWidgets.QLabel("Форма для заполнения отсутствует")
            no_form_label.setAlignment(QtCore.Qt.AlignCenter)
            self.form_layout.addWidget(no_form_label)
            return
        
        # Заголовок формы
        title = form_config.get("title", "Протокол измерений")
        title_label = QtWidgets.QLabel(title)
        title_label.setObjectName("formTitle")
        self.form_layout.addWidget(title_label)
        
        # Поля формы
        fields = form_config.get("fields", [])
        self.form_widgets = {}  # Сбрасываем виджеты формы для нового задания
        
        for field in fields:
            field_label = QtWidgets.QLabel(field["label"])
            field_label.setObjectName("fieldLabel")
            self.form_layout.addWidget(field_label)
            
            if field["type"] == "double":
                # Поле с подполями (например, "в помещении" и "вне помещения")
                subfield_layout = QtWidgets.QHBoxLayout()
                
                for subfield in field.get("subfields", []):
                    subfield_widget = QtWidgets.QWidget()
                    subfield_inner_layout = QtWidgets.QVBoxLayout(subfield_widget)
                    
                    subfield_label = QtWidgets.QLabel(subfield["label"])
                    
                    # Если поле только для чтения (фактические значения), отображаем как текст
                    if subfield.get("readonly", False):
                        value_label = QtWidgets.QLabel(subfield.get("value", ""))
                        self.form_layout.addWidget(subfield_label)
                        self.form_layout.addWidget(value_label)
                    else:
                        # Поле для ввода нормативного значения
                        subfield_input = QtWidgets.QLineEdit()
                        subfield_input.setPlaceholderText("Введите значение...")
                        
                        # Сохраняем ссылку на виджет для доступа к данным
                        field_key = f"{field['label']}_{subfield['label']}"
                        self.form_widgets[field_key] = subfield_input
                        
                        subfield_inner_layout.addWidget(subfield_label)
                        subfield_inner_layout.addWidget(subfield_input)
                    
                    subfield_layout.addWidget(subfield_widget)
                
                self.form_layout.addLayout(subfield_layout)
                
            elif field["type"] == "select":
                # Выпадающий список
                if "subfields" in field:
                    # Несколько выпадающих списков
                    subfield_layout = QtWidgets.QHBoxLayout()
                    
                    for subfield in field["subfields"]:
                        subfield_widget = QtWidgets.QWidget()
                        subfield_inner_layout = QtWidgets.QVBoxLayout(subfield_widget)
                        
                        subfield_label = QtWidgets.QLabel(subfield["label"])
                        subfield_combo = QtWidgets.QComboBox()
                        subfield_combo.addItems(subfield["options"])
                        
                        field_key = f"{field['label']}_{subfield['label']}"
                        self.form_widgets[field_key] = subfield_combo
                        
                        subfield_inner_layout.addWidget(subfield_label)
                        subfield_inner_layout.addWidget(subfield_combo)
                        subfield_layout.addWidget(subfield_widget)
                    
                    self.form_layout.addLayout(subfield_layout)
                else:
                    # Один выпадающий список
                    combo = QtWidgets.QComboBox()
                    combo.addItems(field["options"])
                    
                    field_key = field["label"]
                    self.form_widgets[field_key] = combo
                    
                    self.form_layout.addWidget(combo)
        
        self.form_layout.addStretch()
    
    def clear_form_layout(self):
        """Полностью очищает layout формы"""
        # Удаляем все виджеты из form_layout
        while self.form_layout.count():
            item = self.form_layout.takeAt(0)
            if item.widget():
                item.widget().deleteLater()
            elif item.layout():
                # Рекурсивно очищаем вложенные layout
                self.clear_nested_layout(item.layout())
    
    def clear_nested_layout(self, layout):
        """Рекурсивно очищает вложенные layout"""
        if layout is None:
            return
        while layout.count():
            item = layout.takeAt(0)
            if item.widget():
                item.widget().deleteLater()
            elif item.layout():
                self.clear_nested_layout(item.layout())

class TestSession:
    def __init__(self, test_data):
        self.test_data = test_data
        self.current_stage = 0
        self.stages = []
        self.test_results = []  # Храним результаты всех тестов
        self.setup_stages()
    
    def setup_stages(self):
        if "theory" in self.test_data:
            self.stages.append({"type": "theory", "data": self.test_data["theory"]})
        
        # Исправлено: используем правильные названия полей
        if "initial_test" in self.test_data:
            questions = self.test_data["initial_test"]
            self.stages.append({"type": "test", "data": questions, "name": "Входной тест", "test_type": "initial"})
        
        if "practice" in self.test_data:
            practice_tasks = self.test_data["practice"]
            self.stages.append({"type": "practice", "data": practice_tasks, "name": "Практические задания"})
        
        if "final_test" in self.test_data:
            questions = self.test_data["final_test"]
            self.stages.append({"type": "test", "data": questions, "name": "Итоговый тест", "test_type": "final"})
    
    def get_current_stage(self):
        if self.current_stage < len(self.stages):
            return self.stages[self.current_stage]
        return None
    
    def next_stage(self):
        if self.current_stage < len(self.stages) - 1:
            self.current_stage += 1
            return True
        return False
    
    def add_test_result(self, test_type: str, correct_count: int, total_questions: int):
        """Добавляет результат теста для итогового подсчета"""
        self.test_results.append({
            'type': test_type,
            'correct_count': correct_count,
            'total_questions': total_questions,
            'percentage': (correct_count / total_questions) * 100 if total_questions > 0 else 0
        })
    
    def get_final_grade(self) -> int:
        """Возвращает итоговую оценку по 10-балльной системе"""
        return calculate_final_grade_10(self.test_results)
    
    def get_progress(self):
        return (self.current_stage + 1, len(self.stages))

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, initial_data: Optional[Dict[str, Any]] = None):
        super().__init__()
        self.setWindowTitle("Учреждение образования БГУИР\nКафедра инженерной психологии и эргономики\nУчебная дисциплина 'Безопасность жизнедеятельности человека'")
        
        # Определяем разрешение экрана и устанавливаем размер окна
        self.screen = QtWidgets.QApplication.primaryScreen()
        self.screen_geometry = self.screen.availableGeometry()
        
        # Устанавливаем размер окна как 85% от разрешения экрана
        self.window_width = int(self.screen_geometry.width() * 0.85)
        self.window_height = int(self.screen_geometry.height() * 0.85)
        self.resize(self.window_width, self.window_height)
        
        # Центрируем окно
        x = (self.screen_geometry.width() - self.window_width) // 2
        y = (self.screen_geometry.height() - self.window_height) // 2
        self.move(x, y)

        # Загружаем стили из файла
        if STYLESHEET.exists():
            try:
                style_content = STYLESHEET.read_text(encoding="utf-8")
                self.setStyleSheet(style_content)
            except Exception:
                pass

        self.tests_data = initial_data or {"tests": []}
        self.current_test_session = None
        self.current_questions = []
        self.question_index = 0
        self.correct_count = 0
        self.start_time = 0
        self.movie = None

        self.central = QtWidgets.QStackedWidget()
        self.setCentralWidget(self.central)

        self.home_widget = self.build_home()
        self.theory_widget = None
        self.test_widget = self.build_test_widget()
        self.practice_widget = None
        self.progress_widget = self.build_progress_widget()
        self.final_results_widget = None

        self.central.addWidget(self.home_widget)
        self.central.addWidget(self.progress_widget)
        self.central.addWidget(self.test_widget)

        self.central.setCurrentWidget(self.home_widget)

    def build_home(self):
        w = QtWidgets.QWidget()
        layout = QtWidgets.QVBoxLayout(w)

        header = QtWidgets.QHBoxLayout()
        title = QtWidgets.QLabel("Учреждение образования\n'Белорусский государственный университет информатики и радиоэлектроники'\nКафедра инженерной психологии и эргономики\n Учебная дисциплина 'Безопасность жизнедеятельности человека'")
        title.setObjectName("titleLabel")
        title.setAlignment(QtCore.Qt.AlignCenter)
        header.addWidget(title)
        header.addStretch()

        layout.addLayout(header)

        desc = QtWidgets.QLabel("")
        desc.setObjectName("descLabel")
        layout.addWidget(desc)

        self.cards_container = QtWidgets.QWidget()
        self.cards_layout = QtWidgets.QVBoxLayout(self.cards_container)
        self.cards_layout.setSpacing(int(self.window_height * 0.02))  # 2% от высоты окна
        scroll = QtWidgets.QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(self.cards_container)
        layout.addWidget(scroll)
        layout.addStretch()

        self.refresh_tests_list()
        return w

    def refresh_tests_list(self):
        for i in reversed(range(self.cards_layout.count())):
            w = self.cards_layout.itemAt(i).widget()
            if w:
                w.deleteLater()

        tests = self.tests_data.get("tests", [])
        if not tests:
            lbl = QtWidgets.QLabel("Нет загруженных учебных модулей")
            lbl.setAlignment(QtCore.Qt.AlignCenter)
            lbl.setObjectName("noTestsLabel")
            self.cards_layout.addWidget(lbl)
            return

        for t in tests:
            card = QtWidgets.QFrame()
            card.setObjectName("card")
            card.setMinimumHeight(int(self.window_height * 0.15))  # 15% от высоты окна
            cl = QtWidgets.QHBoxLayout(card)
            cl.setSpacing(int(self.window_width * 0.03))  # 3% от ширины окна
            cl.setContentsMargins(
                int(self.window_width * 0.02),
                int(self.window_height * 0.02),
                int(self.window_width * 0.02),
                int(self.window_height * 0.02)
            )
            
            left = QtWidgets.QVBoxLayout()
            left.setSpacing(int(self.window_height * 0.01))  # 1% от высоты окна
            title_txt = t.get("title") or t.get("test_name") or "Без названия"
            lbl = QtWidgets.QLabel(title_txt)
            lbl.setObjectName("titleLabel")
            lbl.setWordWrap(True)
            left.addWidget(lbl)
            desc = QtWidgets.QLabel(t.get("description", ""))
            desc.setObjectName("descLabel")
            desc.setWordWrap(True)
            left.addWidget(desc)
            cl.addLayout(left)
            cl.addStretch()
            right = QtWidgets.QVBoxLayout()
            btn = QtWidgets.QPushButton("Начать обучение")
            btn.setObjectName("primary")
            btn.setMinimumSize(int(self.window_width * 0.12), int(self.window_height * 0.06))  # 12% ширины, 6% высоты
            btn.clicked.connect(lambda checked, tt=t: self.start_test_session(tt))
            right.addWidget(btn)
            right.addStretch()
            cl.addLayout(right)
            self.cards_layout.addWidget(card)

    def start_test_session(self, test_obj: Dict[str, Any]):
        base = test_obj.get("_source_base") or self.tests_data.get("_base_path") or str(APP_DIR)
        test_obj["_source_base"] = base
        
        self.current_test_session = TestSession(test_obj)
        self.show_current_stage()

    def show_current_stage(self):
        stage = self.current_test_session.get_current_stage()
        if not stage:
            self.finish_session()
            return
        
        stage_type = stage["type"]
        
        if stage_type == "theory":
            self.show_theory_stage(stage)
        elif stage_type == "test":
            self.show_test_stage(stage)
        elif stage_type == "practice":
            self.show_practice_stage(stage)
        
        self.update_progress_display()

    def show_theory_stage(self, stage):
        theory_content = stage["data"]
        base_path = self.current_test_session.test_data.get("_source_base", str(APP_DIR))
        
        self.theory_widget = TheoryWidget(theory_content, base_path)
        
        if self.central.indexOf(self.theory_widget) == -1:
            self.central.addWidget(self.theory_widget)
        
        self.central.setCurrentWidget(self.theory_widget)
        
        next_btn = QtWidgets.QPushButton("Перейти к тесту")
        next_btn.setObjectName("primary")
        next_btn.setMinimumSize(int(self.window_width * 0.12), int(self.window_height * 0.06))
        next_btn.clicked.connect(self.next_stage)
        
        if self.theory_widget.layout() is not None:
            existing_layout = self.theory_widget.layout()
            for i in reversed(range(existing_layout.count())):
                item = existing_layout.itemAt(i)
                if isinstance(item, QtWidgets.QHBoxLayout):
                    existing_layout.removeItem(item)
        
        nav_layout = QtWidgets.QHBoxLayout()
        nav_layout.addStretch()
        nav_layout.addWidget(next_btn)
        
        if self.theory_widget.layout() is not None:
            self.theory_widget.layout().addLayout(nav_layout)

    def show_test_stage(self, stage):
        self.current_questions = shuffle_questions(stage["data"])
        self.question_index = 0
        self.correct_count = 0
        self.start_time = time.time()
        
        test_name = stage.get("name", "Тест")
        self.test_title_label.setText(test_name)
        
        self._render_question()
        self.central.setCurrentWidget(self.test_widget)

    def show_practice_stage(self, stage):
        practice_data = stage["data"]
        base_path = self.current_test_session.test_data.get("_source_base", str(APP_DIR))
        
        self.practice_widget = PracticeWidget(practice_data, base_path, self)  # Передаем self как main_window
        
        if self.central.indexOf(self.practice_widget) == -1:
            self.central.addWidget(self.practice_widget)

        self.central.setCurrentWidget(self.practice_widget)

    def next_stage(self):
        """Переход к следующему этапу с проверкой выполнения практики"""
        current_stage = self.current_test_session.get_current_stage()
        
        # Если текущий этап - практика, проверяем выполнение всех заданий
        if current_stage and current_stage["type"] == "practice":
            if hasattr(self, 'practice_widget') and self.practice_widget:
                all_passed = all(
                    self.practice_widget.form_results.get(f"task_{i}", {}).get("is_passed", False)
                    for i in range(len(current_stage["data"]))
                )
                
                if not all_passed:
                    QtWidgets.QMessageBox.warning(self, "Внимание", 
                        "Не все практические задания выполнены! Завершите все задания перед переходом к итоговому тесту.")
                    return
        
        # Переход к следующему этапу
        if self.current_test_session.next_stage():
            self.show_current_stage()
        else:
            self.finish_session()

    def update_progress_display(self):
        current, total = self.current_test_session.get_progress()
        self.progress_label.setText(f"Этап {current} из {total}")

    def build_progress_widget(self):
        w = QtWidgets.QWidget()
        layout = QtWidgets.QVBoxLayout(w)
        
        self.progress_label = QtWidgets.QLabel("Этап 1 из 4")
        self.progress_label.setObjectName("titleLabel")
        self.progress_label.setAlignment(QtCore.Qt.AlignCenter)
        layout.addWidget(self.progress_label)
        
        return w

    def build_test_widget(self):
        w = QtWidgets.QWidget()
        v = QtWidgets.QVBoxLayout(w)
        v.setSpacing(int(self.window_height * 0.02))  # 2% от высоты окна

        top = QtWidgets.QHBoxLayout()
        self.test_title_label = QtWidgets.QLabel("")
        self.test_title_label.setObjectName("test_title_label")
        top.addWidget(self.test_title_label)
        top.addStretch()
        self.counter_label = QtWidgets.QLabel("")
        self.counter_label.setObjectName("counter_label")
        top.addWidget(self.counter_label)
        v.addLayout(top)

        self.question_text = QtWidgets.QLabel("")
        self.question_text.setObjectName("question_text")
        self.question_text.setWordWrap(True)
        self.question_text.setMinimumHeight(int(self.window_height * 0.08))  # 8% от высоты окна
        v.addWidget(self.question_text)

        self.image_label = QtWidgets.QLabel()
        self.image_label.setObjectName("image_label")
        self.image_label.setAlignment(QtCore.Qt.AlignCenter)
        self.image_label.setMinimumSize(
            int(self.window_width * 0.6),
            int(self.window_height * 0.4)
        )
        self.image_label.setScaledContents(False)
        self.image_label.hide()
        v.addWidget(self.image_label)

        self.answers_layout = QtWidgets.QVBoxLayout()
        self.answers_layout.setObjectName("answers_layout")
        self.answers_layout.setSpacing(int(self.window_height * 0.01))  # 1% от высоты окна
        v.addLayout(self.answers_layout)

        bottom = QtWidgets.QHBoxLayout()
        self.progress = QtWidgets.QProgressBar()
        self.progress.setMinimumHeight(int(self.window_height * 0.03))  # 3% от высоты окна
        bottom.addWidget(self.progress)
        self.next_button = QtWidgets.QPushButton("Далее")
        self.next_button.setObjectName("next_button")
        self.next_button.setMinimumSize(
            int(self.window_width * 0.1),
            int(self.window_height * 0.05)
        )
        self.next_button.clicked.connect(self.on_next)
        self.next_button.setEnabled(False)
        bottom.addWidget(self.next_button)
        v.addLayout(bottom)

        return w

    def _render_question(self):
        self._clear_layout(self.answers_layout)

        if getattr(self, "movie", None):
            try:
                self.movie.stop()
            except Exception:
                pass
            self.movie = None
            self.image_label.clear()
            self.image_label.hide()

        if not self.current_questions or self.question_index >= len(self.current_questions):
            self.finish_test_stage()
            return

        q = self.current_questions[self.question_index]
        text = q.get("question") or q.get("text") or "(нет текста вопроса)"
        total = len(self.current_questions)
        self.counter_label.setText(f"Вопрос {self.question_index + 1} из {total}")
        self.question_text.setText(f"{self.question_index + 1}. {text}")
        self.next_button.setEnabled(False)

        img_field = q.get("image")
        if img_field:
            imgpath = resolve_image_field(img_field, self.current_test_session.test_data.get("_source_base", str(APP_DIR)))
            if imgpath and os.path.exists(imgpath):
                if imgpath.lower().endswith(".gif"):
                    try:
                        self.movie = QtGui.QMovie(imgpath)
                        self.image_label.setMovie(self.movie)
                        self.movie.start()
                        self.image_label.show()
                    except Exception:
                        self.image_label.hide()
                else:
                    try:
                        pix = QtGui.QPixmap(imgpath)
                        if not pix.isNull():
                            # Адаптивное масштабирование под размер окна
                            max_width = int(self.window_width * 0.6)
                            max_height = int(self.window_height * 0.4)
                            scaled_pix = pix.scaled(
                                max_width,
                                max_height,
                                QtCore.Qt.KeepAspectRatio,
                                QtCore.Qt.SmoothTransformation
                            )
                            self.image_label.setPixmap(scaled_pix)
                            self.image_label.show()
                        else:
                            self.image_label.hide()
                    except Exception:
                        self.image_label.hide()
            else:
                self.image_label.hide()
        else:
            self.image_label.hide()

        choices = q.get("options") or q.get("choices") or q.get("answers") or []
        self.answer_buttons = []
        correct_raw = q.get("correct") if "correct" in q else q.get("answer", None)
        is_multiple = isinstance(correct_raw, list)
        qtype = q.get("type", "multiple" if is_multiple else "single")

        for idx, ch in enumerate(choices):
            btn = QtWidgets.QPushButton(str(ch))
            btn.setCheckable(True)
            btn.setProperty("idx", idx)
            btn.clicked.connect(lambda checked, b=btn, qt=qtype: self._on_answer_click(b, qt))
            btn.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
            btn.setMinimumHeight(int(self.window_height * 0.05))  # 5% от высоты окна
            self.answers_layout.addWidget(btn)
            self.answer_buttons.append(btn)

        self.progress.setMaximum(len(self.current_questions))
        self.progress.setValue(self.question_index + 1)

    def _on_answer_click(self, btn: QtWidgets.QPushButton, qtype: str):
        if qtype == "single":
            for b in self.answer_buttons:
                b.setEnabled(False)

            q = self.current_questions[self.question_index]
            correct_raw = q.get("correct") if "correct" in q else q.get("answer", None)
            
            if isinstance(correct_raw, list):
                correct = [int(x) for x in correct_raw]
            elif correct_raw is None:
                correct = []
            else:
                try:
                    correct = [int(correct_raw)]
                except Exception:
                    opts = q.get("options") or q.get("choices") or q.get("answers") or []
                    try:
                        idx = opts.index(correct_raw)
                        correct = [idx]
                    except Exception:
                        correct = []

            idx_clicked = btn.property("idx")
            if idx_clicked in correct:
                btn.setProperty("correct", "true")
                btn.style().unpolish(btn)
                btn.style().polish(btn)
                self.correct_count += 1
            else:
                btn.setProperty("incorrect", "true")
                btn.style().unpolish(btn)
                btn.style().polish(btn)
                for b in self.answer_buttons:
                    if b.property("idx") in correct:
                        b.setProperty("correct", "true")
                        b.style().unpolish(b)
                        b.style().polish(b)
            self.next_button.setEnabled(True)

        else:
            any_selected = any(b.isChecked() for b in self.answer_buttons)
            self.next_button.setEnabled(any_selected)

    def on_next(self):
        q = self.current_questions[self.question_index]
        correct_raw = q.get("correct") if "correct" in q else q.get("answer", None)
        is_multiple = isinstance(correct_raw, list)
        if is_multiple:
            if isinstance(correct_raw, list):
                correct = [int(x) for x in correct_raw]
            else:
                try:
                    correct = [int(correct_raw)]
                except Exception:
                    correct = []
            selected = [i for i, b in enumerate(self.answer_buttons) if b.isChecked()]
            for b in self.answer_buttons:
                b.setEnabled(False)
            for b in self.answer_buttons:
                idx = b.property("idx")
                if idx in correct:
                    b.setProperty("correct", "true")
                    b.style().unpolish(b)
                    b.style().polish(b)
            incorrect_selected = [i for i in selected if i not in correct]
            for b in self.answer_buttons:
                if b.property("idx") in incorrect_selected:
                    b.setProperty("incorrect", "true")
                    b.style().unpolish(b)
                    b.style().polish(b)
            if set(selected) == set(correct):
                self.correct_count += 1

        QtCore.QTimer.singleShot(300, self._advance_or_finish)

    def _advance_or_finish(self):
        self.question_index += 1
        if self.question_index >= len(self.current_questions):
            self.finish_test_stage()
        else:
            self._render_question()

    def finish_test_stage(self):
        total = len(self.current_questions)
        score = self.correct_count
        incorrect_count = total - score
        pct = int(score / total * 100) if total else 0
        elapsed = int(time.time() - self.start_time) if self.start_time else 0
        grade_10 = calculate_grade_10(score, total)

        # Сохраняем результат теста для итогового подсчета
        current_stage = self.current_test_session.get_current_stage()
        test_type = current_stage.get("test_type", "unknown")
        self.current_test_session.add_test_result(test_type, score, total)

        result_text = f"""
<b>Результаты теста:</b>

Правильные ответы: {score} из {total}
Неправильные ответы: {incorrect_count}
Процент выполнения: {pct}%
Оценка по 10-балльной системе: {grade_10}/10
Время выполнения: {elapsed} сек.
        """

        msg = QtWidgets.QMessageBox(self)
        msg.setWindowTitle("Тест завершён")
        msg.setTextFormat(QtCore.Qt.RichText)
        msg.setText(result_text)
        
        btn_continue = msg.addButton("Продолжить", QtWidgets.QMessageBox.ActionRole)
        
        msg.exec_()

        self.next_stage()

    def finish_session(self):
        """Завершение всей учебной сессии с показом итоговой оценки по 10-балльной системе"""
        # Рассчитываем итоговую оценку по 10-балльной системе
        final_grade_10 = self.current_test_session.get_final_grade()
        grade_description = get_grade_description_10(final_grade_10)
        
        # Создаем виджет с итоговыми результатами
        self.final_results_widget = self.build_final_results_widget(final_grade_10, grade_description)
        
        if self.central.indexOf(self.final_results_widget) == -1:
            self.central.addWidget(self.final_results_widget)
        
        self.central.setCurrentWidget(self.final_results_widget)

    def build_final_results_widget(self, final_grade: int, grade_description: str):
        """Создает виджет с итоговыми результатами по 10-балльной системе"""
        widget = QtWidgets.QWidget()
        layout = QtWidgets.QVBoxLayout(widget)
        layout.setSpacing(int(self.window_height * 0.02))  # 2% от высоты окна
        layout.setContentsMargins(
            int(self.window_width * 0.05),
            int(self.window_height * 0.05),
            int(self.window_width * 0.05),
            int(self.window_height * 0.05)
        )
        
        # Заголовок
        title = QtWidgets.QLabel("Обучение завершено!")
        title.setObjectName("finalTitle")
        title.setAlignment(QtCore.Qt.AlignCenter)
        title.setMinimumHeight(int(self.window_height * 0.1))  # 10% от высоты окна
        layout.addWidget(title)
        
        # Итоговая оценка
        grade_widget = QtWidgets.QWidget()
        grade_layout = QtWidgets.QVBoxLayout(grade_widget)
        
        grade_label = QtWidgets.QLabel(f"Итоговая оценка: {final_grade}/10")
        grade_label.setObjectName("finalGrade")
        grade_label.setAlignment(QtCore.Qt.AlignCenter)
        grade_label.setMinimumHeight(int(self.window_height * 0.08))  # 8% от высоты окна
        grade_layout.addWidget(grade_label)
        
        description_label = QtWidgets.QLabel(grade_description)
        description_label.setObjectName("gradeDescription")
        description_label.setAlignment(QtCore.Qt.AlignCenter)
        grade_layout.addWidget(description_label)
        
        layout.addWidget(grade_widget)
        
        # Детальная статистика по тестам
        stats_widget = self.build_detailed_stats_widget()
        layout.addWidget(stats_widget, 1)
        
        # Кнопка возврата на главную
        btn_home = QtWidgets.QPushButton("На главную")
        btn_home.setObjectName("primary")
        btn_home.setMinimumSize(
            int(self.window_width * 0.15),
            int(self.window_height * 0.06)
        )
        btn_home.clicked.connect(lambda: self.central.setCurrentWidget(self.home_widget))
        layout.addWidget(btn_home, 0, QtCore.Qt.AlignCenter)
        
        return widget

    def build_detailed_stats_widget(self):
        """Создает виджет с детальной статистикой по всем тестам (текстом, без таблицы)"""
        widget = QtWidgets.QWidget()
        layout = QtWidgets.QVBoxLayout(widget)
        layout.setSpacing(int(self.window_height * 0.015))  # 1.5% от высоты окна
        layout.setContentsMargins(
            int(self.window_width * 0.03),
            int(self.window_height * 0.03),
            int(self.window_width * 0.03),
            int(self.window_height * 0.03)
        )

        # Заголовок
        stats_title = QtWidgets.QLabel("📊 Детальная статистика:")
        stats_title.setObjectName("detailedStatsTitle")
        layout.addWidget(stats_title)

        # Формируем текст отчёта
        report_lines = []
        test_results = self.current_test_session.test_results

        for result in test_results:
            test_type = "Входной тест" if result['type'] == 'initial' else "Итоговый тест"
            correct = result['correct_count']
            total = result['total_questions']
            percentage = result['percentage']

            # Цветовая метка (эмодзи)
            if percentage >= 80:
                status = "✅ Высокий результат"
            elif percentage >= 50:
                status = "⚠️ Средний результат"
            else:
                status = "❌ Низкий результат"

            block = (
                f"<b>{test_type}</b><br>"
                f"Правильных ответов: <b>{correct}</b><br>"
                f"Всего вопросов: <b>{total}</b><br>"
                f"Процент: <b>{percentage:.1f}%</b> — {status}<br><br>"
            )
            report_lines.append(block)

        # Собираем весь текст
        report_text = "".join(report_lines)

        stats_report = QtWidgets.QLabel(report_text)
        stats_report.setWordWrap(True)
        stats_report.setObjectName("detailedStatsReport")
        layout.addWidget(stats_report)

        info_label = QtWidgets.QLabel(
            "Система оценивания:\n"
            "• Входной тест: 50% от итоговой оценки\n"
            "• Итоговый тест: 50% от итоговой оценки\n"
            "• Итоговая оценка выставляется по 10-балльной системе"
        )
        info_label.setObjectName("infoLabel")
        layout.addWidget(info_label)

        return widget

    def open_test_file(self):
        fn, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Загрузить учебный модуль", str(APP_DIR), "JSON files (*.json)")
        if not fn:
            return
        try:
            data = load_tests_from_file(Path(fn))
            if "tests" in data:
                self.tests_data = data
            else:
                self.tests_data = {"tests": [data], "_base_path": str(Path(fn).parent)}
            self.refresh_tests_list()
            QtWidgets.QMessageBox.information(self, "Успех", "Учебный модуль успешно загружен.")
        except Exception as e:
            QtWidgets.QMessageBox.critical(self, "Ошибка", f"Ошибка загрузки: {e}")

    def _clear_layout(self, layout: QtWidgets.QLayout):
        while layout.count():
            item = layout.takeAt(0)
            w = item.widget()
            if w:
                w.deleteLater()

def main():
    logger.info("Запуск TestsApp")
    initial = None
    if DEFAULT_TEST_FILE.exists():
        try:
            initial = load_tests_from_file(DEFAULT_TEST_FILE)
        except Exception:
            pass

    app = QtWidgets.QApplication(sys.argv)
    
    # Установка масштабирования для высоких DPI дисплеев
    if hasattr(QtCore.Qt, 'AA_EnableHighDpiScaling'):
        app.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling, True)
    if hasattr(QtCore.Qt, 'AA_UseHighDpiPixmaps'):
        app.setAttribute(QtCore.Qt.AA_UseHighDpiPixmaps, True)
    
    window = MainWindow(initial or {"tests": []})
    window.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()