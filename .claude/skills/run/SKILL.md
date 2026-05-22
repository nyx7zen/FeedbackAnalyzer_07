# Run Skill - Execute TODO Phase Item

This skill executes a specific Feedback Analyzer TODO phase item (e.g., SPEC-01-01, RED-02-04).

For the complete skill definition, workflow, guardrails, and output patterns, see the source skill:

[.agents/skills/run/SKILL.md](../../.agents/skills/run/SKILL.md)

## Quick Reference

**Usage Examples:**
- `/run RED-02-04` - Execute TODO item RED-02-04
- `SPEC-01-02 진행해 주세요` - Execute SPEC-01-02 (Korean)
- `1번 실행` - Execute prompt item #1 (mapped via prompts/INDEX.md)

**Workflow:**
1. Read AGENTS.md, TODO.md
2. Resolve item identifier (from ID or prompts/INDEX.md)
3. Inspect related source, tests, docs
4. Apply changes per TODO scope
5. Run build/tests if code changes
6. Update TODO checkbox and SESSION_NOTES.md

See [.agents/skills/run/SKILL.md](../../.agents/skills/run/SKILL.md) for full details.
