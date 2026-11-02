/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:22:24 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/22 12:22:26 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

// ==================== CORE CLASS ====================
template <typename T>
class PmergeMeCore
{
public:
    // Public entry point
    template <typename Iterator>
    static void sort_impl(Iterator begin, Iterator end)
    {
        if (std::distance(begin, end) <= 1)
            return;

        // 1. Pair elements
        std::vector<T> winners;
        std::vector<T> losers;
        T odd;
        bool has_odd = pair_elements(begin, end, winners, losers, odd);

        // 2. Recursively sort winners
        sort_impl(winners.begin(), winners.end());

        // 3. Insert losers using Jacobsthal
        std::vector<T> result;
        insert_losers(winners, losers, result);

        // 4. Insert odd element if needed
        if (has_odd)
            insert_odd(result, odd);

        // 5. Copy sorted result back
        copy_back(result, begin);
    }

private:
    // ==================== 1. Pair Elements ====================
    template <typename Iterator>
    static bool pair_elements(Iterator begin, Iterator end,
                              std::vector<T>& winners,
                              std::vector<T>& losers,
                              T& odd)
    {
        Iterator it = begin;
        while (it + 1 < end)
        {
            if (*it < *(it + 1))
            {
                winners.push_back(*(it + 1));
                losers.push_back(*it);
            }
            else
            {
                winners.push_back(*it);
                losers.push_back(*(it + 1));
            }
            it += 2;
        }

        bool has_odd = (std::distance(begin, end) % 2 == 1);
        if (has_odd)
            odd = *(end - 1);

        return has_odd;
    }

    // ==================== 2. Insert Losers with Jacobsthal ====================
    static void insert_losers(const std::vector<T>& winners,
                              const std::vector<T>& losers,
                              std::vector<T>& result)
    {
        if (winners.empty())
            return;

        result.push_back(winners[0]); // first winner
        size_t inserted = 0;
        size_t j = 2;

        while (inserted < losers.size())
        {
            size_t prev = jacobsthal(j - 1);
            size_t curr = jacobsthal(j);
            size_t batch = curr - prev;

            for (size_t k = 0; k < batch && inserted < losers.size(); ++k)
            {
                // Insert loser using binary search
                typename std::vector<T>::iterator pos =
                    std::upper_bound(result.begin(), result.end(), losers[inserted]);
                result.insert(pos, losers[inserted]);
                ++inserted;
            }
            ++j;
        }

        // Append remaining winners
        for (size_t i = 1; i < winners.size(); ++i)
            result.push_back(winners[i]);
    }

    // ==================== 3. Insert Odd Element ====================
    static void insert_odd(std::vector<T>& result, const T& odd)
    {
        typename std::vector<T>::iterator pos =
            std::upper_bound(result.begin(), result.end(), odd);
        result.insert(pos, odd);
    }

    // ==================== 4. Copy back to original container ====================
    template <typename Iterator>
    static void copy_back(const std::vector<T>& sorted, Iterator out)
    {
        for (size_t i = 0; i < sorted.size(); ++i)
            *(out++) = sorted[i];
    }

    // ==================== Jacobsthal Numbers ====================
    static size_t jacobsthal(size_t n)
    {
        if (n == 0) return 0;
        if (n == 1) return 1;
        size_t a = 0, b = 1;
        for (size_t i = 2; i <= n; ++i)
        {
            size_t c = b + 2 * a;
            a = b;
            b = c;
        }
        return b;
    }
};

// ==================== WRAPPERS ====================

// Vector wrapper
template <typename T>
void PmergeMe(std::vector<T>& v)
{
    PmergeMeCore<T>::sort_impl(v.begin(), v.end());
}

// Deque wrapper
template <typename T>
void PmergeMe(std::deque<T>& d)
{
    PmergeMeCore<T>::sort_impl(d.begin(), d.end());
}
*/
