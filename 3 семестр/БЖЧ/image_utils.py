# image_utils.py
import requests
import hashlib
from pathlib import Path
from appdirs import user_cache_dir
from PIL import Image
from io import BytesIO
import logging

logger = logging.getLogger("TestsApp.image_utils")

# cache dir in user cache (cross-platform)
CACHE_DIR = Path(user_cache_dir("tests_app")) / "images"
CACHE_DIR.mkdir(parents=True, exist_ok=True)

IMAGE_EXTS = {'.png', '.jpg', '.jpeg', '.gif', '.bmp', '.webp'}

def is_url(s: str) -> bool:
    return isinstance(s, str) and s.startswith(("http://", "https://"))

def cache_image_from_url(url: str) -> str:
    try:
        h = hashlib.sha256(url.encode("utf-8")).hexdigest()
        ext = Path(url).suffix or ".png"
        if ext.lower() not in IMAGE_EXTS:
            ext = ".png"
        target = CACHE_DIR / f"{h}{ext}"
        if target.exists():
            return str(target)
        resp = requests.get(url, timeout=10)
        resp.raise_for_status()
        img = Image.open(BytesIO(resp.content))
        img.save(target)
        return str(target)
    except Exception as e:
        logger.exception("Ошибка загрузки изображения по URL %s: %s", url, e)
        return None

def resolve_image_field(image_field, test_base) -> str:
    """
    :
      - None -> None
      - URL -> download & cache -> path
      - absolute path -> if exists
      - relative path -> relative to test_base, then app dir, then as given
    """
    if not image_field:
        return None
    s = str(image_field).strip()
    if is_url(s):
        return cache_image_from_url(s)
    p = Path(s)
    # absolute
    if p.is_absolute():
        if p.exists() and p.suffix.lower() in IMAGE_EXTS:
            return str(p)
        return None
    # relative to provided base
    try:
        cand = Path(test_base) / p
        if cand.exists() and cand.suffix.lower() in IMAGE_EXTS:
            return str(cand)
    except Exception:
        pass
    # relative to project assets
    cand2 = Path(__file__).parent.parent / p
    if cand2.exists() and cand2.suffix.lower() in IMAGE_EXTS:
        return str(cand2)
    # try direct
    cand3 = Path(s)
    if cand3.exists() and cand3.suffix.lower() in IMAGE_EXTS:
        return str(cand3)
    logger.debug("Не найдено изображение для %s", s)
    return None
