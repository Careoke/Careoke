from pathlib import Path
import re

SRC = Path("utils")
OUT = Path("out/utils")

EXTENSIONS = {
    ".mp3",
    ".png",
}


def make_identifier(path: Path) -> str:
    name = path.stem
    name = re.sub(r"[^a-zA-Z0-9_]", "_", name)

    if name[0].isdigit():
        name = "_" + name

    return name


for src_file in SRC.rglob("*"):
    if not src_file.is_file():
        continue

    if src_file.suffix.lower() not in EXTENSIONS:
        continue

    relative = src_file.relative_to(SRC)

    out_dir = OUT / relative.parent
    out_dir.mkdir(parents=True, exist_ok=True)

    out_file = out_dir / f"{src_file.stem}.h"

    name = make_identifier(src_file)
    guard = name.upper() + "_H"

    data = src_file.read_bytes()

    with out_file.open("w") as f:
        f.write(f"#ifndef {guard}\n")
        f.write(f"#define {guard}\n\n")
        f.write("#include <stddef.h>\n\n")

        f.write(f"static const unsigned char {name}[] = {{\n")

        for i in range(0, len(data), 16):
            chunk = data[i:i + 16]
            f.write("    ")
            f.write(", ".join(f"0x{byte:02X}" for byte in chunk))
            f.write(",\n")

        f.write("};\n\n")
        f.write(f"static const size_t {name}_size = sizeof({name});\n\n")

        f.write(f"#endif /* {guard} */\n")

    print(f"{src_file} -> {out_file}")