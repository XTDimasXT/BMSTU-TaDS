#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "queue_array.h"

void init_arr_queue(arr_t *queue)
{
    queue->begin = -1;
    queue->end = -1;
    queue->size = 0;
}

int owerflow_arr_queue(arr_t queue)
{
    return (queue.size == 1000) ? 1 : 0;
}

int clear_check_arr_queue(arr_t queue)
{
    return queue.begin == -1 ? 1 : 0;
}

void push_arr_queue(arr_t *queue, int elem)
{    
    if (queue->begin == -1)
    {
        queue->begin = 0;
    }

    queue->end = (queue->end + 1) % MAX_ELEMS;
    queue->arr[queue->end] = elem;
    queue->size++;
}

void pop_arr_queue(arr_t *queue)
{
    if (queue->begin == queue->end)
    {
        queue->begin = -1;
        queue->end = -1;
    }
    else
    {
        queue->begin = (queue->begin + 1) % MAX_ELEMS;
        queue->size--;
    }
}


void print_arr_queue(arr_t queue)
{
    if (clear_check_arr_queue(queue))
    {
        printf("\nОчередь пустая\n");
        return;
    }

    puts("\n");

    for (int i = queue.begin; i <= queue.end; i++)
        printf("%d ", queue.arr[i]);

    puts("\n");
}


float min_of_three(float a, float b, float c)
{
    float min = a;

    if (min > b)
        min = b;
    if (min > c)
        min = c;

    return min;
}

void task_arr(void)
{
    arr_t queue1;
    init_arr_queue(&queue1);

    int q1_req_in = 0;
    int q1_req_out = 0;
    int q1_req_all = 0;
    int q1_len_all = 0;
    float q1_time_all = 0;
    int q1_len_cur = 0;

    arr_t queue2;
    init_arr_queue(&queue2);

    int q2_req_in = 0; 
    int q2_req_out = 0;
    int q2_req_all = 0;
    int q2_len_all = 0;
    float q2_time_all = 0;
    int q2_len_cur = 0;
    int q2_back_in_end = 0;

    float q1_cur_time_in = 0;
    float q2_cur_time_in = 0;

    int queue_type = 0;
    float oa_time = 0;

    float time_all = 0;

    int to_show = 0;

    int in_push = 0, in_pop = 0;

    while (q1_req_out < 1000)
    {
        if (q1_cur_time_in == 0)
            q1_cur_time_in = rand_time(T1_IN_B, T1_IN_E);

        if (q2_cur_time_in == 0)
            q2_cur_time_in = rand_time(T2_IN_B, T2_IN_E);

        if (oa_time == 0)
        {
            if (!clear_check_arr_queue(queue1))
            {
                oa_time = rand_time(T1_OUT_B, T1_OUT_E);
                queue_type = 1;
                pop_arr_queue(&queue1);

                in_pop++;

                q1_len_cur--;
                q1_req_all++;
                q1_len_all += q1_len_cur;

                q1_time_all += oa_time;
            }
            else if (!clear_check_arr_queue(queue2))
            {
                oa_time = rand_time(T2_OUT_B, T2_OUT_E);
                queue_type = 2;
                pop_arr_queue(&queue2);

                q2_len_cur--;
                q2_req_all++;
                q2_len_all += q2_len_cur;

                q2_time_all += oa_time;
            }            
        }
        else if ((queue_type == 2) && (!clear_check_arr_queue(queue2)))
        {
            push_arr_queue(&queue2, 2);
            q2_time_all -= oa_time;
            oa_time = 0;
            q2_back_in_end++;

            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
            continue;
        }

        float min_time = 0;

        if (oa_time == 0)
            min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, q1_cur_time_in);
        else
            min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, oa_time);

        if (oa_time == min_time)
        {
            oa_time = 0;

            if (queue_type == 1)
                q1_req_out++;
            else if (queue_type == 2)
                q2_req_out++;
        }

        if (q1_cur_time_in == min_time)
        {
            push_arr_queue(&queue1, 1);

            in_push++;

            q1_req_in++;
            q1_len_cur++;
            q1_req_all++;
            q1_len_all += q1_len_cur;
        }

        if (q2_cur_time_in == min_time)
        {
            push_arr_queue(&queue2, 2);

            q2_req_in++;
            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
        }

        q1_cur_time_in -= min_time;
        q2_cur_time_in -= min_time;

        if (oa_time >= min_time)
            oa_time -= min_time;

        time_all += min_time;

        if ((q1_req_out % 100 == 0) && (q1_req_out != to_show))
        {
            to_show = q1_req_out;
            printf("\nЗаявок 1го типа обработано = %d\n", q1_req_out);

            printf("Текущая длина очереди 1го типа = %d\n", q1_len_cur);
            printf("Средняя длина очереди 1го типа = %f\n", ((float)q1_len_all / q1_req_all));

            printf("Текущая длина очереди 2го типа = %d\n", q2_len_cur);
            printf("Средняя длина очереди 2го типа = %f\n\n", ((float)q2_len_all / q2_req_all));
        }

    }

    float avg_q1_in = (T1_IN_B + T1_IN_E) / 2;
    float all_avg_q1_in = avg_q1_in * COUNT;

    float avg_q1_out = (T1_OUT_B + T1_OUT_E) / 2;
    float all_avg_q1_out = avg_q1_out * COUNT;

    float avg_q2_in = (float)(T2_IN_B + T2_IN_E) / (float)2;

    float estimate_model_time;

    if (all_avg_q1_in > all_avg_q1_out)
        estimate_model_time = all_avg_q1_in;
    else
        estimate_model_time = all_avg_q1_out;

    float percent_oa = fabs((time_all - estimate_model_time) * 100 / estimate_model_time);

    printf("\nОбщее время моделировния = %f \
    \nПогрешность моделирования = %.2f%%\n", time_all, percent_oa);

    printf("\nЗаявок вошло в 1ую очередь = %d \
    \nЗаявок 1ой очереди вышло = %d \
    \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %f\n", q1_req_in, q1_req_out, avg_q1_in);

    printf("\nЗаявок вошло во 2ую очередь = %d \
    \nЗаявок 2ой очереди вышло = %d \
    \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %f\
    \nЗаявок 2го типа вернулось обратно в конец очереди = %d\n", q2_req_in, q2_req_out, avg_q2_in, q2_back_in_end);

    float time_in1 = time_all / avg_q1_in;
    float percent_time_in1 = fabs((q1_req_in - time_in1) * 100 / time_in1);

    float time_in2 = time_all / avg_q2_in;
    float percent_time_in2 = fabs((q2_req_in - time_in2) * 100 / time_in2);

    printf("\nПогрешность ввода заявок в 1ую очередь %.2f%% \
    \nПогрешность ввода заявок во 2ую очередь %.2f%%\n", percent_time_in1, percent_time_in2);

    float all_estimate_work = q1_time_all + q2_time_all;
    float time_wait = time_all - all_estimate_work;

    printf("\nВремя простоя = %.2f\n", fabs(time_wait));
}