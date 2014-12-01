
import hook_tools

hooks = [
    'pre-commit'
]

pre_commit_checks = [
    hook_tools.cpplint_check,
    hook_tools.pep8lint_check,
    hook_tools.jsonlint_check
]
