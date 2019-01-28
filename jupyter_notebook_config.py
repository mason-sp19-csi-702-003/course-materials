c.FilesWriter.build_directory = "build"
c.LatexExporter.template_file = "classicm"
c.NbConvertApp.output_files_dir = "."
c.PDFExporter.latex_command = [
    "xelatex",
    "-8bit",
    "-shell-escape",
    "{filename}",
]
c.RSTExporter.file_extension = ".rst"
