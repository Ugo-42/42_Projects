# Commit Message Policy

We follow a simplified version of the Conventional Commits specification to keep our repository history clean, scannable, and structured. 

All commit messages are automatically validated by a local pre-commit hook before they can be accepted into the repository history.

---

## 1. Structure of a Commit Message

Commit messages must strictly follow this structure:

```
<type>(<scope>): <description>

[optional body paragraphs]
```

*Note: The `(<scope>)` section is optional, but heavily encouraged.*

---

## 2. Validation Rules

Our automated checker enforces the following rules strictly. If any rule is broken, your commit will be rejected instantly:

### Type Rules
The `<type>` prefix tells the team what kind of change you are introducing. You must use one of these allowed keywords:
* **feat**: A new feature or enhancement.
* **fix**: A bug fix.
* **docs**: Documentation-only changes (README modifications, inline comments).
* **style**: Code formatting, missing semi-colons, white-space fixes (no logic changes).
* **refactor**: Rewriting or restructuring code without changing its behavior or fixing bugs.
* **perf**: Performance-improving code changes.
* **test**: Adding missing tests or refactoring/correcting existing tests.
* **chore**: Build tasks, package dependency updates, or CI/CD configuration files.

### Scope Rules
* The scope must be wrapped in matching parentheses `()`.
* If a scope is provided, it **must be longer than 1 character**. Single-character scopes will fail validation.
* Try to keep scopes tied to major structural modules (e.g., `game`, `auth`, `ui`, `docker`, `database`).

### Description Rules
* A colon followed by a single space (`: `) is strictly required between the type/scope and the description text.
* The description **must be more than one word**. Short, single-word descriptions like `feat(api): updates` or `fix: bug` will be blocked. Write concise, meaningful summaries.

---

## 3. Local Hooks Setup

To activate the automated validation checker across your local development environment, run the following command combo from the root directory of your project:

```bash
git pull && git config core.hooksPath .githooks/
```

This updates your local Git configuration to look inside our versioned `.githooks/` directory whenever you execute a `git commit`. 

### The Commit Flow
1. Run your normal `git commit -m "..."` command.
2. The hook script parses your text. If it fails formatting rules, a red **COMMIT REJECTED** block appears alongside the reason, and the commit drops out.
3. If it passes structural analysis, a green **COMMIT VALIDATION** block appears, outputting your exact commit message for review.
4. You will be interactively prompted to reread your text for typos. You must manually press `y` to finalize it.
5. If you omitted a scope, a secondary warning prompt will explicitly double-check if you intended to commit without one.

---

## 3. Best Practices (Mixed Commits)

### Keep Commits Atomic
Each commit should represent **one logical change**. Do not group multiple unrelated changes or types into a single commit message. 

* **Bad (Mixed Intent):** `feat(auth): add google sign-in and fix navbar alignment when fullscreen` 
* **Good (Split Intent):** Make two separate commits instead:
  1. `feat(auth): add google sign-in`
  2. `fix(ui): fix navbar alignment when fullscreen`

### What if I already ran `git add .`?
If you accidentally staged your entire folder together but realized the changes should be split up into multiple distinct commits:

1. **Un-stage everything safely** without losing any of your actual code modifications by running:
```bash
   git reset
```
2. Add and commit file one by one
```bash
git add src/auth.cpp && git commit -m "feat(auth): add google sign-in"
```

Then

```bash
git add src/game.cpp && git commit -m "fix(ui): fix navbar alignment when fullscreen"
```
