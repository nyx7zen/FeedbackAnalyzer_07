# Status Skill - Show Project Progress

This skill displays current branch, phase, TODO progress, changed files, verification state, and next recommended TODO items.

Two modes supported:
- Quick snapshot-based status ("상태")
- Refreshed current status with full inspection ("상태갱신" or phase-specified)

For the complete skill definition, workflow, output format, snapshot mechanism, and guardrails, see the source skill:

[.agents/skills/status/SKILL.md](../../.agents/skills/status/SKILL.md)

## Quick Reference

**Quick Mode (Fast, snapshot-based):**
- `/status` - Show last known status from snapshot
- `상태` - Korean: show quick status
- `현재 상태를 보여주세요.` - Show current status

**Refreshed Mode (Accurate, full inspection):**
- `상태갱신` - Refresh and show current state
- `갱신` - Refresh state (shorthand for 상태갱신)
- `상태 새로고침` - Refresh status
- `현재 진행 현황을 보여주세요` - Show detailed status
- `/status red` - Show RED phase items (auto-refresh)
- `/status REFACTOR-03` - Show REFACTOR-03 items (auto-refresh)
- `브랜치` - Show branch status
- `할일` - Show TODO items

**Output Format:**
- Branch progress tree (main → B_07 → phase branches)
- Working tree changes
- Current phase
- Completed TODO items
- Pending TODO items
- Next recommended items (table format)
- Last verification status

**Snapshot:**
- Location: .agents/skills/status/STATUS_SNAPSHOT.md
- Updated only in Refreshed mode
- Used for delta comparison and next-item recommendations

See [.agents/skills/status/SKILL.md](../../.agents/skills/status/SKILL.md) for full details.
