/* $Id$ */
/** @file
 * kRbTmpl - Templated Red-Black Trees, Get Best Fitting Node.
 */

/*
 * Copyright (c) 1999-2009 Knut St. Osmundsen <bird-kStuff-spamix@anduin.net>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Finds the best fitting node in the tree for the given Key value.
 *
 * @returns Pointer to the best fitting node found.
 * @param   pRoot           Pointer to the Red-Back tree's root structure.
 * @param   Key             The Key of which is to be found a best fitting match for..
 * @param   fAbove          K_TRUE:  Returned node is have the closest key to Key from above.
 *                          K_FALSE: Returned node is have the closest key to Key from below.
 * @sketch  The best fitting node is always located in the searchpath above you.
 *          >= (above): The node where you last turned left.
 *          <= (below): the node where you last turned right.
 */
KRB_DECL(KRBNODE *) KRB_FN(GetBestFit)(KRBROOT *pRoot, KRBKEY Key, KBOOL fAbove)
{
    register KRBNODE  *pNode;
    KRBNODE           *pNodeLast;

    KRB_READ_LOCK(pLook);
    if (pRoot->mpRoot == KRB_NULL)
    {
        KRB_READ_UNLOCK(pLook);
        return NULL;
    }

    pNode = KRB_GET_POINTER(&pRoot->mpRoot);
    pNodeLast = NULL;
    if (fAbove)
    {   /* pNode->mKey >= Key */
        while (KRB_CMP_NE(pNode->mKey, Key))
        {
            if (KRB_CMP_G(pNode->mKey, Key))
            {
                if (pNode->mpLeft == KRB_NULL)
                {
                    KRB_READ_UNLOCK(pLook);
                    return pNode;
                }
                pNodeLast = pNode;
                pNode = KRB_GET_POINTER(&pNode->mpLeft);
            }
            else
            {
                if (pNode->mpRight == KRB_NULL)
                {
                    KRB_READ_UNLOCK(pLook);
                    return pNodeLast;
                }
                pNode = KRB_GET_POINTER(&pNode->mpRight);
            }
        }
    }
    else
    {   /* pNode->mKey <= Key */
        while (KRB_CMP_NE(pNode->mKey, Key))
        {
            if (KRB_CMP_G(pNode->mKey, Key))
            {
                if (pNode->mpLeft == KRB_NULL)
                {
                    KRB_READ_UNLOCK(pLook);
                    return pNodeLast;
                }
                pNode = KRB_GET_POINTER(&pNode->mpLeft);
            }
            else
            {
                if (pNode->mpRight == KRB_NULL)
                {
                    KRB_READ_UNLOCK(pLook);
                    return pNode;
                }
                pNodeLast = pNode;
                pNode = KRB_GET_POINTER(&pNode->mpRight);
            }
        }
    }

    /* perfect match or nothing. */
    KRB_READ_UNLOCK(pLook);
    return pNode;
}

