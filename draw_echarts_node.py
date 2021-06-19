from pyecharts.charts import Bar, Page, Line
from pyecharts import options as opts

# 准备不同稠密程度下节点数量影响的绘制数据

list1 = []
list2 = []
list3 = []
cnt = 0
modes = ["equalEdge", "permutationEdge", "randomEdge"]
for attri in ['sparse', 'dense']:
    for mode in modes:
        list1.append([])
        list2.append([])
        list3.append([])
        for i in range(2000, 21000, 2000):
            j = 0 if attri == 'sparse' else i - 1
            with open(f"./recordData_bynode/kruskal_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list1[cnt].append(float(f.read()))
            with open(f"./recordData_bynode/prim_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list2[cnt].append(float(f.read()))
            with open(f"./recordData_bynode/primHeap_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list3[cnt].append(float(f.read()))
        with open(f"./out/bn_kruskal_{mode}_{str(j)}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        with open(f"./out/bn_prim_{mode}_{str(j)}.txt", 'w', encoding='utf-8') as f:
            for item in list2[cnt]:
                print(item, file=f)
        with open(f"./out/bn_primHeap_{mode}_{str(j)}.txt", 'w', encoding='utf-8') as f:
            for item in list3[cnt]:
                print(item, file=f)
        cnt += 1

# 绘制不同稠密程度下节点数量的影响

page = Page(page_title = "最小生成树算法对比_bynode",
        layout=Page.SimplePageLayout)

xaxis = [j for j in range(2000, 21000, 2000)]
cnt = 0
for attri in ['sparse', 'dense']:
    bar = Bar().add_xaxis(xaxis)
    bar.add_yaxis(f"kruskal equalEdge", list1[cnt+0])
    bar.add_yaxis(f"kruskal permutationEdge", list1[cnt+1])
    bar.add_yaxis(f"kruskal randomEdge", list1[cnt+2])
    bar.add_yaxis(f"prim equalEdge", list2[cnt+0])
    bar.add_yaxis(f"prim permutationEdge", list2[cnt+1])
    bar.add_yaxis(f"prim randomEdge", list2[cnt+2])
    bar.add_yaxis(f"primHeap equalEdge", list3[cnt+0])
    bar.add_yaxis(f"primHeap permutationEdge", list3[cnt+1])
    bar.add_yaxis(f"primHeap randomEdge", list3[cnt+2])
    bar.set_global_opts(
        title_opts=opts.TitleOpts(title="最小生成树算法对比", subtitle=f"{attri}"),
        tooltip_opts=opts.TooltipOpts(trigger="axis"),
        # toolbox_opts=opts.ToolboxOpts(is_show=True),
        legend_opts=opts.LegendOpts(pos_top='bottom')
    )
    bar.set_series_opts(label_opts=opts.LabelOpts(is_show=False))
    # bar.render(f"./out/bn_{str(j)}.html")
    page.add(bar)
    cnt += 3
page.render("节点数.html")