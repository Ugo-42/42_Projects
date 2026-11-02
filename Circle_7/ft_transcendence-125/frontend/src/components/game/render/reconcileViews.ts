/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  reconcileViews.ts                                      ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/08/25 11:43:35 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/08/25 11:43:43 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

export interface Keyed {
	id: string;
}

export function reconcileViews<T extends Keyed, V>(
	views: Map<string, V>,
	latest: T[],
	create: (item: T) => V,
	update: (view: V, item: T) => void,
	destroy: (view: V) => void,
) {
	const latestIds = new Set(latest.map((item) => item.id));

	for (const [id, view] of views) {
		if (!latestIds.has(id)) {
			destroy(view);
			views.delete(id);
		}
	}

	for (const item of latest) {
		const existing = views.get(item.id);
		if (existing) update(existing, item);
		else views.set(item.id, create(item));
	}
}
