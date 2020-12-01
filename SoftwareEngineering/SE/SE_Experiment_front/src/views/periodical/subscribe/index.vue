<template>
  <div>
    <el-row>
      <el-col :span="18" :offset="5" style="margin-top: 50px;">
        <el-table
          :data="tableData"
          border
          style="width: 80%"
        >
          <el-table-column
            fixed
            prop="journalNo"
            label="编号"
            width="150"
          />
          <el-table-column
            prop="period"
            label="期刊类型"
            width="120"
          />
          <el-table-column
            prop="journalName"
            label="期刊名"
            width="120"
          />
          <el-table-column
            show-overflow-tooltip
            prop="description"
            label="描述"
            width="300"
          />
          <el-table-column
            fixed="right"
            label="操作"
            width="120"
          >
            <template slot-scope="scope">
              <el-button type="danger" @click="cancel_subscripe(scope.row)">取消订阅</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="8">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="[5, 10, 20]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </el-col>
    </el-row>
  </div>
</template>

<script>
import { searchSubscribe } from '../../../api/periodical'
import { cancelSubscribe } from '../../../api/periodical'

export default {
  name: 'PeriodicalSubscribe',
  data() {
    return {
      tableData: [],
      keyword: '',
      pageSize: 5,
      currentPage: 1,
      total: 0
    }
  },
  computed: {},
  created() {
    this.search()
  },
  methods: {
    search() {
      searchSubscribe({
        stuId: this.$store.getters.userId, pageNum: this.currentPage, pageSize: this.pageSize
      }).then(response => {
        this.tableData = response.data.list,
        this.pageSize = response.data.size,
        this.currentPage = response.data.pageNum,
        this.total = response.data.total,
        console.log(this.tableData[0].description)
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    cancel_subscripe(row) {
      cancelSubscribe({ stuId: this.$store.getters.userId, journalNo: row.journalNo }).then(response => {
        this.$message({
          type: 'success',
          message: response.msg
        })
        this.search()
      })
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
