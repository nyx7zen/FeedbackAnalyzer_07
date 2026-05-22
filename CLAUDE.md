# Feedback Analyzer_07

## Project Overview

- **Language:** C++17, CMake 3.14+, cpp-httplib
- **Purpose:** Legacy refactoring, test coverage, state management
- **Repository:** Windows MinGW environment (primary)

## Execution Model

This project uses phase-based learning workflow managed through Codex skills.

For complete project instructions, see [AGENTS.md](AGENTS.md).

## Skills

The project provides two custom skills for execution and status tracking:

### /run - Execute TODO Phase Item

Execute a specific TODO phase item (e.g., SPEC-01-01, RED-02-04).

Usage: `/run RED-02-04` or `SPEC-01-02 진행해 주세요` or `1번 실행`

See [.agents/skills/run/SKILL.md](.agents/skills/run/SKILL.md) for workflow and guardrails.

### /status - Show Project Progress

Display current branch, phase, TODO progress, and next items.

Usage: `/status` or `/status red` or `상태`

See [.agents/skills/status/SKILL.md](.agents/skills/status/SKILL.md) for output format and snapshot mechanism.

## Key Paths

- **Detailed Instructions:** [AGENTS.md](AGENTS.md)
- **Phase TODOs:** [TODO.md](TODO.md)
- **Phase Prompts:** [prompts/INDEX.md](prompts/INDEX.md)
- **Session Notes:** [SESSION_NOTES.md](SESSION_NOTES.md)
- **Skill Definitions:** [.agents/skills/](.agents/skills/)
