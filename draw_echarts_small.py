# 准备平均情况下稠密度影响因素的绘制数据
from pyecharts.charts import Bar, Page, Line
from pyecharts import options as opts
list1 = []
list2 = []
cnt = 0
for i in [100, 200, 500]:
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        list1.append([])
        list2.append([])
        for j in range(i):
            with open(f"./recordData/kruskal_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list1[cnt].append(float(f.read()))
            with open(f"./recordData/prim_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list2[cnt].append(float(f.read()))
        with open(f"./out/kruskal_{str(i)}_{mode}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        with open(f"./out/prim_{str(i)}_{mode}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        cnt += 1

# 绘制平均情况下稠密度影响因素的对比图
page = Page(page_title="最小生成树算法对比",
            layout=Page.SimplePageLayout)

cnt = 0
for i in [100, 200, 500]:
    xaxis = [j for j in range(1, i+1)]
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        line = Line().add_xaxis(xaxis)
        line.add_yaxis(f"kruskal {mode}", list1[cnt])
        line.add_yaxis(f"prim {mode}", list2[cnt])
        cnt += 1
        line.set_global_opts(
            title_opts=opts.TitleOpts(
                title="最小生成树算法对比", subtitle=f"规模为{str(i)}-{mode}"),
            # tooltip_opts=opts.TooltipOpts(trigger="axis"),
            # toolbox_opts=opts.ToolboxOpts(is_show=True),
        )
        line.set_series_opts(label_opts=opts.LabelOpts(is_show=False))
        line.render(f"./out/{str(i)}-{mode}.html")
        page.add(line)
page.render("稠密度.html")

# 准备星状图稠密度影响因素的绘制数据

list1 = []
list2 = []
cnt = 0
for i in [100, 200, 500]:
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        list1.append([])
        list2.append([])
        for j in range(i):
            with open(f"./recordData_pernode/kruskal_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list1[cnt].append(float(f.read()))
            with open(f"./recordData_pernode/prim_{str(i)}_{mode}.txt_{str(j)}.txt", 'r', encoding='utf-8') as f:
                list2[cnt].append(float(f.read()))
        with open(f"./out/pn_kruskal_{str(i)}_{mode}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        with open(f"./out/pn_prim_{str(i)}_{mode}.txt", 'w', encoding='utf-8') as f:
            for item in list1[cnt]:
                print(item, file=f)
        cnt += 1

page = Page(page_title="最小生成树算法对比_pernode",
            layout=Page.SimplePageLayout)

cnt = 0
for i in [100, 200, 500]:
    xaxis = [j for j in range(1, i+1)]
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        line = Line().add_xaxis(xaxis)
        line.add_yaxis(f"kruskal {mode}", list1[cnt])
        line.add_yaxis(f"prim {mode}", list2[cnt])
        cnt += 1
        line.set_global_opts(
            title_opts=opts.TitleOpts(
                title="最小生成树算法对比", subtitle=f"规模为{str(i)}-{mode}"),
            # tooltip_opts=opts.TooltipOpts(trigger="axis"),
            # toolbox_opts=opts.ToolboxOpts(is_show=True),
        )
        line.set_series_opts(label_opts=opts.LabelOpts(is_show=False))
        line.render(f"./out/pn_{str(i)}-{mode}.html")
        page.add(line)
page.render("稠密度-pernode.html")

# 准备不同稠密程度下节点数量影响的绘制数据

list1 = []
list2 = []
cnt = 0
for j in [0, 64]:
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        list1.append([])
        list2.append([])
        for i in range(100, 2100, 100):
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
# print(list1, list2)

# 绘制不同稠密程度下节点数量的影响

page = Page(page_title="最小生成树算法对比_bynode",
            layout=Page.SimplePageLayout)

cnt = 0
xaxis = [j for j in range(100, 2100, 100)]
for i in [0, 64]:
    bar = Bar().add_xaxis(xaxis)
    for mode in ["equalEdge", "permutationEdge", "randomEdge"]:
        bar.add_yaxis(f"kruskal {mode}", list1[cnt])
        bar.add_yaxis(f"prim {mode}", list2[cnt])
        cnt += 1
        bar.set_global_opts(
            title_opts=opts.TitleOpts(
                title="最小生成树算法对比", subtitle=f"度数为{str(i)}"),
            tooltip_opts=opts.TooltipOpts(trigger="axis"),
            toolbox_opts=opts.ToolboxOpts(is_show=True),
            legend_opts=opts.LegendOpts(pos_top='bottom')
        )
        bar.set_series_opts(label_opts=opts.LabelOpts(is_show=False))
        # bar.render(f"./out/bn_{str(i)}-{mode}.html")
    bar.render(f"./out/bn_{str(j)}.html")
    page.add(bar)
page.render("节点数.html")
