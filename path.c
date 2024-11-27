//
// Created by Rayane Karaouzene on 27/11/2024.
//

#include "path.h"

t_path findbestpath(t_node *root,int currentcost,t_move* currentsequence,int movecount)
{
    t_path result = {INT_MAX,INT_MAX,NULL,0};

    if(!root)
    {
        return result;
    }

    currentcost+=root->value;

    if(isleafnode(root))
    {
        if(root->value<result.minval)
        {
            result.movesequence = (t_move*)malloc((movecount+1)*sizeof (t_move));

            for (int i = 0; i < movecount; ++i) {
                result.movesequence[i] = currentsequence[i];
            }

            result.movesequence[movecount]=root->move;

            result.minval = root->value;
            result.totalcost = currentcost;
            result.movecount = movecount+1;
        }
    }

    for (int i = 0; i < root->nbSons; ++i) {
        if(root->sons[i]==NULL)continue;

        t_move newsequence[movecount+1];

        for (int j = 0; j < movecount; ++j) {
            newsequence[j] = currentsequence[j];

        }

        newsequence[movecount]=root->sons[i]->move;

        t_path childresult = findbestpath(root->sons[i],currentcost,newsequence,movecount+1);

        if (childresult.minval<result.minval){
            result = childresult;
        }
    }
    return result;
}