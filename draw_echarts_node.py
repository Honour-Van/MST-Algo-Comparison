from pyecharts.charts import Bar, Page, Line
from pyecharts import options as opts

# 准备不同稠密程度下节点数量影响的绘制数据

list1 = []
list2 = []
cnt = 0
for attri in ['sparse', 'dense']:
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        list1.append([])
        list2.append([])
        for i in range(2000, 21000, 1000):
            j = 0 if attri == 'sparse' else i - 1
            with open(f"./recordData_bynode/kruskal_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list1[cnt].append(float(f.read()))
            with open(f"./recordData_bynode/prim_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list2[cnt].append(float(f.read()))
        with open(f"./out/bn_kruskal_{mode}_{str(j)}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        with open(f"./out/bn_prim_{mode}_{str(j)}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        cnt += 1

# 绘制不同稠密程度下节点数量的影响

page = Page(page_title = "最小生成树算法对比_bynode",
        layout=Page.SimplePageLayout)

cnt = 0
xaxis = [j for j in range(2000, 21000, 1000)]
for attri in ['sparse', 'dense']:
    bar = Bar().add_xaxis(xaxis)
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        bar.add_yaxis(f"kruskal {mode}", list1[cnt])
        bar.add_yaxis(f"prim {mode}", list2[cnt])
        cnt += 1
        bar.set_global_opts(
            title_opts=opts.TitleOpts(title="最小生成树算法对比", subtitle=f"{attri}"),
            tooltip_opts=opts.TooltipOpts(trigger="axis"),
            # toolbox_opts=opts.ToolboxOpts(is_show=True),
            legend_opts=opts.LegendOpts(pos_top='bottom')
        )
        bar.set_series_opts(label_opts=opts.LabelOpts(is_show=False))
    bar.render(f"./out/bn_{str(j)}.html")
    page.add(bar)
page.render("节点数.html")